#include "../JuceLibraryCode/JuceHeader.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>

namespace NodeAudio {
  class PluginInterface: private juce::InterprocessConnection {
  public:
    PluginInterface(const std::string& uuid): juce::InterprocessConnection(false), pipeName(uuid) {
      createPipe(pipeName, receiveMessageTimeoutMs, true);
    }

    void displayGUI();
    void hideGUI();
    void shutdown();

    void connectionMade() override {}
    void connectionLost() override {}
    void messageReceived(const juce::MemoryBlock &message) override {}
  private:
    const std::string& pipeName;
    int receiveMessageTimeoutMs = 200;
  };

  class PluginInterfaceHost: private juce::InterprocessConnection {
    public:
    PluginInterfaceHost(const std::string& uuid): juce::InterprocessConnection(true), pipeName(uuid) {
      connectToPipe(pipeName, receiveMessageTimeoutMs);
    }

    void connectionMade() override {}
    void connectionLost() override {}
    void messageReceived(const juce::MemoryBlock &message) override;

    virtual void displayGUI() = 0;
    virtual void hideGUI() = 0;
    virtual void shutdown() = 0;
  private:
    const std::string& pipeName;
    int receiveMessageTimeoutMs = 200;
  };
}
