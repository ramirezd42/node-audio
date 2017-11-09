#include "LabSound/core/AudioNodeInput.h"
#include "LabSound/core/AudioNodeOutput.h"
#include "internal/AudioBus.h"

#include "PluginNode.h"

using namespace lab;
using namespace NodeAudio;

PluginNode::PluginNode(std::string _pluginPath, float sampleRate): AudioNode(sampleRate),
                                                                   proc_uuid(boost::uuids::random_generator()()),
                                                                   pluginPath(_pluginPath),
                                                                   interface(boost::uuids::to_string(proc_uuid)),
                                                                   hostProc(_pluginPath, boost::uuids::to_string(proc_uuid)) {
  addInput(std::unique_ptr<AudioNodeInput>(new AudioNodeInput(this)));
  addOutput(std::unique_ptr<AudioNodeOutput>(new AudioNodeOutput(this, 2)));
  initialize();
}

PluginNode::~PluginNode() {
  uninitialize();
}

void PluginNode::process(ContextRenderLock & r, size_t framesToProcess) {
  AudioBus* outputBus = output(0)->bus(r);
  ASSERT(outputBus);
  unsigned numOutputChannels = outputBus->numberOfChannels();
  bool isOutputSafe = outputBus && numOutputChannels == 2 && framesToProcess <= outputBus->length();
  ASSERT(isOutputSafe);

  AudioBus* inputBus = input(0)->bus(r);
  ASSERT(inputBus);
  unsigned numInputChannels = inputBus->numberOfChannels();
  bool isInputSafe = inputBus && numInputChannels == 2 && framesToProcess <= inputBus->length();
  ASSERT(isInputSafe);

  if (!isInitialized() || !input(0)->isConnected())
    outputBus->zero();
  else {
    const float* sourceL = inputBus->channel(0)->data();
    const float* sourceR = inputBus->channel(1)->data();
    float* destL = inputBus->channel(0)->mutableData();
    float* destR = inputBus->channel(1)->mutableData();
    size_t numSamples = outputBus->length();
    hostProc.process(sourceL, sourceR, destL, destR, numSamples);
    outputBus->copyFrom(*inputBus);
  }
}

void PluginNode::reset(ContextRenderLock &) {
  // No-op
}

void PluginNode::initialize() {
  if (isInitialized()) {
    return;
  }
  hostProc.openProcess();
  AudioNode::initialize();
}

void PluginNode::uninitialize() {
  // TODO: Implement stub
  if (!isInitialized()) {
    return;
  }
  hostProc.closeProcess();
  AudioNode::uninitialize();
}

void PluginNode::displayGUI() {
  interface.displayGUI();
}
void PluginNode::hideGUI() {
  interface.hideGUI();
}
