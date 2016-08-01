path = require 'path'

module.exports = (grunt) ->
  grunt.file.setBase(path.resolve('..'))
  require('load-grunt-tasks')(grunt)
  grunt.loadTasks('_build/tasks')

  grunt.initConfig

    pkg: grunt.file.readJSON('package.json')

    clean:
      dist: 'dist'

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

  grunt.registerTask('validate', [ 'coffeelint' ])
  grunt.registerTask('compile-addon', [ 'node-gyp:configure', 'build-espeak-ng', 'node-gyp:build' ])
  