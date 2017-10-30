#ifndef NodeAudioConfig_h
#define NodeAudioConfig_h

#include <string>
#include "nbind/nbind.h"

class NodeAudioConfig {
public:
  static std::string modulePath;
  static void setModulePath(const std::string& path) {
    modulePath = path;
  }
};

NBIND_CLASS(NodeAudioConfig) {
  method(setModulePath);
}

#endif // NodeAudioConfig_h