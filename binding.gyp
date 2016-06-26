{
  "targets": [
    {
      "target_name": "espeak",
      "sources": [
        "src/add-on/espeak.cpp",
        "src/add-on/espeak-addon.cpp",
        "src/add-on/espeak-wrapper.cpp",
        "src/add-on/helpers.cpp"
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        "src/add-on/include/espeak-ng/src/include"
      ]
    }
  ]
}