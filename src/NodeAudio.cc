#include <string>
#include <iostream>

#include "LabSound/extended/LabSound.h"
#include "nbind/nbind.h"

using namespace lab;

namespace NodeAudio {
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

  NBIND_CLASS(NodeAudio) {
    method(MakeAudioContext, "makeAudioContext");
    method(MakeHardwareSourceNode, "makeHardwareSourceNode");
  };
}
