{
  "targets": [
    {
      "includes": [
        "auto.gypi",
        "labsound.gypi",
        "sources.gypi",
      ],

      "sources": [
        "src/module.cc"
      ],
     
      "defines": [
        'OPUS_BUILD',
        'USE_ALLOCA'
      ],
      "conditions": [[ 
        'OS=="mac"', 
        { 
          'defines': [ 
            '__MACOSX_CORE__' 
          ], 
          'link_settings': { 
            'libraries': [ 
              '$(SDKROOT)/System/Library/Frameworks/Accelerate.framework', 
              '$(SDKROOT)/System/Library/Frameworks/AudioToolbox.framework', 
              '$(SDKROOT)/System/Library/Frameworks/AudioUnit.framework', 
              '$(SDKROOT)/System/Library/Frameworks/Carbon.framework', 
              '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework', 
              '$(SDKROOT)/System/Library/Frameworks/CoreAudio.framework'
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
