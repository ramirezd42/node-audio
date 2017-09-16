// #include <nan.h>
// #include "AudioContextWrapper.h"
// #include "HardwareSourceNodeWrapper.h"

// void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
//   Nan::HandleScope scope;

//   AudioContextWrapper::Init(exports);
//   HardwareSourceNodeWrapper::Init(exports);
// }

// NODE_MODULE(addon, InitAll)
#include <string>
#include <iostream>

#include "LabSound/extended/LabSound.h"
#include "nbind/nbind.h"

using namespace lab;

class NodeAudio {
public: 
  static std::shared_ptr<lab::AudioContext> MakeAudioContext() {
  return lab::MakeAudioContext();
  }
  
  static std::shared_ptr<lab::AudioHardwareSourceNode> MakeHardwareSourceNode(std::shared_ptr<lab::AudioContext> context) {
    std::shared_ptr<AudioHardwareSourceNode> input;
    {
        ContextGraphLock g(context, "NodeAudio");
        ContextRenderLock r(context, "NodeAudio");
        input = lab::MakeHardwareSourceNode(r);
    }
    return input;
  }
};

NBIND_CLASS(AudioContext) {
  method(isInitialized);
  method(destination);
  method(isOfflineContext);
  method(currentSampleFrame);
  method(currentTime);
  method(sampleRate);
  method(connectionCount);
};

NBIND_CLASS(AudioNode) {
  method(isScheduledNode);
  method(isInitialized);
  method(channelCount);
  method(sampleRate);
  method(tailTime);
  method(latencyTime);
  method(propagatesSilence);
  method(params);
  multimethod(connect, args(AudioContext*, AudioNode*, unsigned, unsigned));
  multimethod(disconnect, args(AudioContext*, unsigned));
  multimethod(disconnect, args(AudioContext*), "disconnectAll");
};

NBIND_CLASS(AudioHardwareSourceNode) {
  inherit(AudioNode);
};

NBIND_CLASS(AudioDestinationNode) {
  inherit(AudioNode);
};

NBIND_CLASS(AudioParam) {
  method(setValue);
  method(name);
  method(minValue);
  method(maxValue);
  method(defaultValue);
  method(units);
  method(smoothedValue);
  method(setValueAtTime);
  method(linearRampToValueAtTime);
  method(exponentialRampToValueAtTime);
  method(setTargetAtTime);
  method(setValueCurveAtTime);
  method(cancelScheduledValues);
}

NBIND_CLASS(GainNode) {
  construct<float>();
  inherit(AudioNode);
  method(gain);
}

NBIND_CLASS(StereoPannerNode) {
  construct<float>();
  inherit(AudioNode);
  method(pan);
}

NBIND_CLASS(NodeAudio) {
  method(MakeAudioContext, "makeAudioContext");
  method(MakeHardwareSourceNode, "makeHardwareSourceNode");
};