#include "PluginInterface.h"

using namespace NodeAudio;

juce::String DISPLAY_GUI_ACTION = "DISPLAY_GUI";
juce::String HIDE_GUI_ACTION = "HIDE_GUI";
juce::String SHUTDOWN_ACTION = "SHUTDOWN";

void PluginInterface::displayGUI() {
  juce::MemoryBlock block(DISPLAY_GUI_ACTION.toUTF8(), DISPLAY_GUI_ACTION.length());
  sendMessage(block);
}

void PluginInterface::hideGUI() {
  juce::MemoryBlock block(HIDE_GUI_ACTION.toUTF8(), HIDE_GUI_ACTION.length());
  sendMessage(block);
}

void PluginInterface::shutdown() {
  juce::MemoryBlock block(SHUTDOWN_ACTION.toUTF8(), SHUTDOWN_ACTION.length());
  sendMessage(block);
}

void PluginInterfaceHost::messageReceived(const juce::MemoryBlock &message) {
  juce::String action = message.toString();
  if (action == DISPLAY_GUI_ACTION) displayGUI();
  else if (action == HIDE_GUI_ACTION) hideGUI();
  else if (action == SHUTDOWN_ACTION) shutdown();
}
