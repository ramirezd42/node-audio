
#ifndef PluginNode_h
#define PluginNode_h

#include <string>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>

#include "LabSound/core/AudioNode.h"
// #include "JuceLibraryCode/JuceHeader.h"
#include "PluginHostParentProcess/PluginHostParentProcess.h"
#include "Shared/PluginInterface.h"

namespace NodeAudio {
  class PluginNode: public lab::AudioNode {

  public:
    PluginNode(std::string _pluginPath, float sampleRate);
    void displayGUI();
    void hideGUI();
    void shutdown();
    virtual ~PluginNode();

  private:
    virtual void process(lab::ContextRenderLock &, size_t framesToProcess) override;
    virtual void reset(lab::ContextRenderLock &) override;

    virtual void initialize() override;
    virtual void uninitialize() override;

    virtual double tailTime() const override { return 0; }
    virtual double latencyTime() const override { return 0; }

    std::string pluginPath;
    boost::uuids::uuid proc_uuid;
    PluginHostParentProcess hostProc;
    PluginInterface interface;
  };
}

#endif // PluginNode_h
