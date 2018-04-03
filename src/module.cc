#include <string>
#include <iostream>

#include "LabSound/extended/LabSound.h"
#include "extended/PluginNode.h"
#include "NodeAudioConfig.h"

#include "nbind/nbind.h"

using namespace lab;
using namespace NodeAudio;

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

NBIND_CLASS(AudioBufferSourceNode) {
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

NBIND_CLASS(PluginNode) {
  construct<std::string, float>();
  inherit(AudioNode);
  method(displayGUI);
  method(hideGUI);
  method(shutdown);
}
