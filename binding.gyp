{
  "targets": [
    {
      'target_name': 'common',
      'type': 'static_library',
      'includes': [
        'juce.gypi'
      ],
      'sources': [
        'src/extended/Shared/PluginInterface.cc'
      ],
      'configurations': {
        'Debug': {
          'defines': ['DEBUG=1', '_DEBUG=1', 'JUCE_DEBUG=1', '__MACOSX_CORE__']
        },
        'Release': {
          'defines': ['NDEBUG=1', '_NDEBUG=1', 'JUCE_DEBUG=0', '__MACOSX_CORE__']
        }
      }
    },

    {
      'target_name': 'plugin-host-child-process',
      'type': 'executable',
      'dependencies': [
        'common'
      ],
      'include_dirs': [
        'third_party/JUCE/modules',
        'third_party/boost_1_65_1'
      ],
      'sources': [
        'src/extended/PluginHostChildProcess/main.cc',
        'src/extended/PluginHostChildProcess/MainComponent.cc',
        'src/extended/PluginHostChildProcess/IPCAudioIODevice.cc'
      ],
      'configurations': {
        'Debug': {
          'defines': ['DEBUG=1', '_DEBUG=1', 'JUCE_DEBUG=1', '__MACOSX_CORE__', 'OPUS_BUILD', 'USE_ALLOCA']
        },
        'Release': {
          'defines': ['NDEBUG=1', '_NDEBUG=1', 'JUCE_DEBUG=0', '__MACOSX_CORE__', 'OPUS_BUILD', 'USE_ALLOCA']
        }
      },
      "conditions": [[ 
        'OS=="mac"', 
        { 
          'link_settings': { 
            'libraries': [ 
              '$(SDKROOT)/System/Library/Frameworks/Accelerate.framework', 
              '$(SDKROOT)/System/Library/Frameworks/AudioToolbox.framework', 
              '$(SDKROOT)/System/Library/Frameworks/AudioUnit.framework', 
              '$(SDKROOT)/System/Library/Frameworks/Carbon.framework', 
              '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework', 
              '$(SDKROOT)/System/Library/Frameworks/CoreAudio.framework',
            ] 
          }, 
          'xcode_settings': { 
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES', 
            'GCC_ENABLE_CPP_RTTI': 'YES' 
          } 
        } 
      ]]
    },

    {
      'target_name': 'node-audio',
     
      'include_dirs': [
        'third_party/JUCE/modules',
        'third_party/boost_1_65_1'
      ],

      "includes": [
        "auto.gypi",
        "labsound.gypi"
      ],
      "sources": [
        "src/module.cc",
        "src/NodeAudioConfig.cc",
        "src/NodeAudio.cc",
        "src/SoundBuffer.cc",
        "src/extended/PluginNode.cc",
        "src/extended/PluginHostParentProcess/PluginHostParentProcess.cc"
      ],
      'dependencies': [
        'common'
      ],
      'configurations': {
        'Debug': {
          'defines': ['DEBUG=1', '_DEBUG=1', 'JUCE_DEBUG=1', '__MACOSX_CORE__', 'OPUS_BUILD', 'USE_ALLOCA']
        },
        'Release': {
          'defines': ['NDEBUG=1', '_NDEBUG=1', 'JUCE_DEBUG=0', '__MACOSX_CORE__', 'OPUS_BUILD', 'USE_ALLOCA']
        }
      },
      "conditions": [[ 
        'OS=="mac"', 
        { 
          'link_settings': { 
            'libraries': [ 
              '$(SDKROOT)/System/Library/Frameworks/Accelerate.framework', 
              '$(SDKROOT)/System/Library/Frameworks/AudioToolbox.framework', 
              '$(SDKROOT)/System/Library/Frameworks/AudioUnit.framework', 
              '$(SDKROOT)/System/Library/Frameworks/Carbon.framework', 
              '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework', 
              '$(SDKROOT)/System/Library/Frameworks/CoreAudio.framework',
            ] 
          }, 
          'xcode_settings': { 
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES', 
            'GCC_ENABLE_CPP_RTTI': 'YES' 
          } 
        } 
      ]]
    }
  ],
  "includes": [
    "auto-top.gypi",
  ],
  
}
