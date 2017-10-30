{
  "include_dirs": [
    'third_party/JUCE/modules',
    'third_party/vst3sdk'
  ],
  'sources': [
    'src/extended/JuceLibraryCode/include_juce_audio_basics.mm',
    'src/extended/JuceLibraryCode/include_juce_audio_devices.mm',
    'src/extended/JuceLibraryCode/include_juce_audio_formats.mm',
    'src/extended/JuceLibraryCode/include_juce_audio_processors.mm',
    'src/extended/JuceLibraryCode/include_juce_audio_utils.mm',
    'src/extended/JuceLibraryCode/include_juce_core.mm',
    'src/extended/JuceLibraryCode/include_juce_cryptography.mm',
    'src/extended/JuceLibraryCode/include_juce_data_structures.mm',
    'src/extended/JuceLibraryCode/include_juce_events.mm',
    'src/extended/JuceLibraryCode/include_juce_graphics.mm',
    'src/extended/JuceLibraryCode/include_juce_gui_basics.mm',
    'src/extended/JuceLibraryCode/include_juce_gui_extra.mm',
    'src/extended/JuceLibraryCode/include_juce_opengl.mm'
  ],
  "conditions": [[ 
    'OS=="mac"', 
    { 
      'link_settings': { 
        'libraries': [ 
          '$(SDKROOT)/System/Library/Frameworks/Accelerate.framework', 
          '$(SDKROOT)/System/Library/Frameworks/AudioToolbox.framework', 
          '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework', 
          '$(SDKROOT)/System/Library/Frameworks/CoreAudio.framework', 
          '$(SDKROOT)/System/Library/Frameworks/CoreAudioKit.framework', 
          '$(SDKROOT)/System/Library/Frameworks/CoreMidi.framework', 
          '$(SDKROOT)/System/Library/Frameworks/IOKit.framework', 
          '$(SDKROOT)/System/Library/Frameworks/OpenGL.framework', 
          '$(SDKROOT)/System/Library/Frameworks/QTKit.framework', 
          '$(SDKROOT)/System/Library/Frameworks/QuartzCore.framework', 
        ] 
      }, 
      'xcode_settings': { 
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES', 
        'GCC_ENABLE_CPP_RTTI': 'YES',
      } 
    } 
  ]]
}