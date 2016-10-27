  {
  "targets": [
    {
      "target_name": "espeak_addon",
      "sources": [
          "src/cpp/compilation-worker.cpp",
        "src/cpp/direct-sound-player.cpp",
                "src/cpp/espeak.cpp",
        "src/cpp/espeak-addon.cpp",
        "src/cpp/espeak-wrapper.cpp",
        "src/cpp/helpers.cpp",
        "src/cpp/speech-worker.cpp",
        "src/cpp/wave-data.cpp",
        "src/cpp/wave-player.cpp"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        "src/cpp/include/espeak-ng/src/include"
      ],
      "libraries" : [
      "libespeak-ng.lib"
      ]
      }
  ]
}
