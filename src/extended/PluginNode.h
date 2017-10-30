
#ifndef PluginNode_h
#define PluginNode_h

#include <string>
#include "LabSound/core/AudioNode.h"
// #include "JuceLibraryCode/JuceHeader.h"
#include "PluginHostParentProcess/PluginHostParentProcess.h"

namespace NodeAudio {
  class PluginNode: public lab::AudioNode {

  public: 
    PluginNode(std::string _pluginPath, float sampleRate);
    void displayGUI();
    void hideGUI();
    virtual ~PluginNode();

  private:
    virtual void process(lab::ContextRenderLock &, size_t framesToProcess) override;
    virtual void reset(lab::ContextRenderLock &) override;
    
    virtual void initialize() override;
    virtual void uninitialize() override;
    
    virtual double tailTime() const override { return 0; }
    virtual double latencyTime() const override { return 0; }

    std::string pluginPath;
    PluginHostParentProcess hostProc;
  };
}

#endif // PluginNode_h