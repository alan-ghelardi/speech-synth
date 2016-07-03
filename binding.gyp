  {
  "targets": [
    {
      "target_name": "espeak_addon",
      "sources": [
        "src/add-on/disposable.cpp",
        "src/add-on/espeak.cpp",
        "src/add-on/espeak-addon.cpp",
        "src/add-on/espeak-wrapper.cpp",
        "src/add-on/helpers.cpp",
        "src/add-on/speech-worker.cpp"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        "src/add-on/include/espeak-ng/src/include"
      ],
      "libraries" : [
      "libespeak-ng.lib"
      ]
      }
  ]
}
