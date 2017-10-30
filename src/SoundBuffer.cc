#include <string>
#include <iostream>

#include "LabSound/extended/LabSound.h"
#include "nbind/nbind.h"

namespace NodeAudio {
  class SoundBuffer {
  public:
    SoundBuffer(const char * path, float sampleRate): buffer(lab::SoundBuffer(path, sampleRate)) {}

    // play a sound on the context directly, starting after a certain delay
    std::shared_ptr<lab::AudioBufferSourceNode> play(std::shared_ptr<lab::AudioContext> context, float when = 0.0f) {
      std::shared_ptr<lab::AudioBufferSourceNode> input;
      {
        lab::ContextGraphLock g(context, "NodeAudio");
        lab::ContextRenderLock r(context, "NodeAudio");
        input = buffer.play(r, when);
      }
      return input;
    }

    // play a sound on a particular node, starting after a certain delay
    std::shared_ptr<lab::AudioBufferSourceNode> play(std::shared_ptr<lab::AudioContext> context, std::shared_ptr<lab::AudioNode> outputNode, float when = 0.0f) {
      std::shared_ptr<lab::AudioBufferSourceNode> input;
      {
        lab::ContextGraphLock g(context, "NodeAudio");
        lab::ContextRenderLock r(context, "NodeAudio");
        input = buffer.play(r, outputNode, when);
      }
      return input;
    }

  private:
    lab::SoundBuffer buffer;
  };

  NBIND_CLASS(SoundBuffer) {
    construct<const char*, float>();
    multimethod(play, args(std::shared_ptr<lab::AudioContext>, float));
    multimethod(play, args(std::shared_ptr<lab::AudioContext>, std::shared_ptr<lab::AudioNode>, float), "playOnNode");
  }
}
