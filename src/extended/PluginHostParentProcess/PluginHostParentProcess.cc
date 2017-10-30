#include "PluginHostParentProcess.h"
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/atomic.hpp>
#include <chrono>
#include <iostream>

using namespace NodeAudio;
using namespace boost::interprocess;

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point call_started;
high_resolution_clock::time_point call_ended = high_resolution_clock::now();

PluginHostParentProcess::PluginHostParentProcess(std::string _pluginPath, std::string _shmemFile) :
    shmemFile(_shmemFile),
    pluginPath(_pluginPath),
    shmemRemover(_shmemFile.data()),
    shm(create_only, shmemFile.data(), read_write)
{

  try {
    //Set size
    shm.truncate(sizeof(SharedMemoryBuffer));

    region = std::unique_ptr<mapped_region> (new mapped_region(
      shm,
      read_write
    ));

    shmemBuffer = new(region->get_address()) SharedMemoryBuffer;
  } catch(interprocess_exception &ex){
    std::cout << "INTERPROCESS EXCEPTION: ";
    std::cout << ex.what() << std::endl;
  }
};
PluginHostParentProcess::~PluginHostParentProcess(){};

void PluginHostParentProcess::process(
  const float* leftChannelInput,
  const float* rightChannelInput,
  float* leftChannelOutput,
  float* rightChannelOutput,
  size_t samplesPerChannel
) {

  call_started = high_resolution_clock::now();
  auto interval = duration_cast<microseconds>(call_started - call_ended).count();
  // cout << "CALL INTEVAL: " << interval << endl;

  scoped_lock<interprocess_mutex> lock(shmemBuffer->mutex);

  for (int sample = 0; sample < SharedMemoryBuffer::BufferSize; sample++) {
    shmemBuffer->buffer[0][sample] = leftChannelInput[sample];
    shmemBuffer->buffer[1][sample] = rightChannelInput[sample];
  }

  shmemBuffer->cond_empty.notify_one();
  shmemBuffer->message_in = true;

  if(shmemBuffer->message_in) {
    shmemBuffer->cond_full.wait(lock);
  }

  for (int sample = 0; sample < SharedMemoryBuffer::BufferSize; sample++) {
    leftChannelOutput[sample] = shmemBuffer->buffer[0][sample];
    rightChannelOutput[sample] = shmemBuffer->buffer[1][sample];
  }

  call_ended = high_resolution_clock::now();
}