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
};

NBIND_CLASS(AudioNode) {
  multimethod(connect, args(AudioContext*, AudioNode*, unsigned, unsigned));
};

NBIND_CLASS(AudioHardwareSourceNode) {
  inherit(AudioNode);
};

NBIND_CLASS(AudioDestinationNode) {
  inherit(AudioNode);
};

NBIND_CLASS(NodeAudio) {
  method(MakeAudioContext, "makeAudioContext");
  method(MakeHardwareSourceNode, "makeHardwareSourceNode");
};