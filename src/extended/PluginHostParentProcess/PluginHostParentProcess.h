
#ifndef PluginHostParentProcess_h
#define PluginHostParentProcess_h

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include "../Shared/SharedMemoryBuffer.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "../../NodeAudioConfig.h"

namespace NodeAudio {

  struct ShmRemove
  {
    const char *segmentFile;
    ShmRemove(const char *id): segmentFile(id) { boost::interprocess::shared_memory_object::remove(segmentFile); }
    ~ShmRemove(){ boost::interprocess::shared_memory_object::remove(segmentFile); }
  };
  
  struct ShmTruncate
  {
    const boost::interprocess::shared_memory_object shm;
    ShmTruncate():shm(){}
  };

  class PluginHostParentProcess {
  public: 
    PluginHostParentProcess(std::string pluginPath, std::string shmemFile);
    ~PluginHostParentProcess();
    
    void openProcess() {
      _process.openProcess(pluginPath, shmemFile);
    }

    void closeProcess(){
      _process.closeProcess();
    }
    void process( const float* leftChannelInput,
                  const float* rightChannelInput,
                  float* leftChannelOutput,
                  float* rightChannelOutput,
                  size_t samplesPerChanne);
  private:

    struct ProcessHandle {
      ProcessHandle() {}
      ~ProcessHandle() { if (process.isRunning()) closeProcess(); }

      void openProcess(std::string pluginPath, std::string shmemFile)
      {
        juce::String dir = juce::String(NodeAudioConfig::modulePath); 
        
        #ifdef DEBUG
          juce::String exec = dir + "/build/Debug/plugin-host-child-process";
        #else
          juce::String exec = dir + "/build/Release/plugin-host-child-process";
        #endif

        juce::StringArray args;
        args.add(exec);
        args.add(juce::String(pluginPath));
        args.add(juce::String(shmemFile));
        std::cout << args.joinIntoString(juce::String(" ")) << std::endl;
        process.start(args);
      }

      void closeProcess() {
        process.kill();
      }

      juce::ChildProcess process;
    };

    ProcessHandle _process;
    

    std::string shmemFile;
    std::string pluginPath;
    ShmRemove shmemRemover;
    boost::interprocess::shared_memory_object shm;
    std::unique_ptr<boost::interprocess::mapped_region> region;
    SharedMemoryBuffer* shmemBuffer;
  };
}

#endif // PluginHostParentProcess_h