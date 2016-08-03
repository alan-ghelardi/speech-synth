path = require 'path'

module.exports = (grunt) ->
  grunt.file.setBase(path.resolve('..'))
  require('load-grunt-tasks')(grunt)
  grunt.loadTasks('_build/tasks')

  grunt.initConfig

    pkg: grunt.file.readJSON('package.json')

    clean:
      build: 'build'
      dist: 'dist'
      'post-build-addon': [
        'build/',
        'src/add-on/include/espeak-ng/src/pcaudiolib/',
        'src/add-on/include/espeak-ng/src/windows/X64/'
      ]

    coffeelint:
      options:
        configFile: 'coffeelint.json'
      build: '_build/**/*.coffee'
      main: 'src/*.coffee'

    coffee:
      options:
        bare: true
      main:
        expand: true
        cwd: 'src'
        src: '*.coffee'
        dest: 'dist',
        ext: '.js'

    copy:
      'pre-build-espeak':
        cwd: 'src/add-on/include'
        expand: true
        src: 'pcaudiolib/**'
        dest: 'src/add-on/include/espeak-ng/src/'

      'post-build-espeak':
        files: [
          {expand: true, flatten: true, src: 'src/add-on/include/espeak-ng/src/windows/X64/Release/libespeak-ng.lib', dest: 'build/'}
          {expand: true, flatten: true, src: 'src/add-on/include/espeak-ng/src/windows/X64/Release/libespeak-ng.dll', dest: 'dist/win32/'}
        ]

      'post-build-addon':
        expand: true
        flatten: true
        src: 'build/Release/espeak_addon.node'
        dest: 'dist/win32/'

  grunt.registerTask('default', [ 'validate', 'compile-addon' ])

  grunt.registerTask('validate', [ 'coffeelint' ])
  
  grunt.registerTask('compile-addon', [
    'node-gyp:configure'
    'copy:pre-build-espeak'
    'build-espeak-ng'
    'copy:post-build-espeak'
    'node-gyp:build'
    'copy:post-build-addon'
    'clean:post-build-addon' ])
