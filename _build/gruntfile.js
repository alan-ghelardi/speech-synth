const path = require('path')

module.exports = (grunt) => {
  grunt.file.setBase(path.resolve('..'))
  require('load-grunt-tasks')(grunt)
  grunt.loadTasks('_build/tasks')

  grunt.initConfig({

    pkg: grunt.file.readJSON('package.json'),

    babel: {
      dist: {
        expand: true,
        flatten : true,
        src: 'src/*.js',
        dest: 'dist'
      }
    },
    
    clean: {
      dist: 'dist',
      'post-build-addon': [
        'build/',
        'src/add-on/include/espeak-ng/src/pcaudiolib/',
        'src/add-on/include/espeak-ng/src/windows/X64/'
      ],
      'post-compile-data': [
        'dist/dictsource',
        'dist/phsource',
      ]
    },

    copy: {
      'pre-build-espeak': {
        cwd: 'src/add-on/include',
        expand: true,
        src: 'pcaudiolib/**',
        dest: 'src/add-on/include/espeak-ng/src/'
      },

      'post-build-espeak': {
        files: [{
          expand: true, 
          flatten: true, 
          src: 'src/add-on/include/espeak-ng/src/windows/X64/Release/libespeak-ng.lib',
          dest: 'build'
        }, { 
          expand: true, 
          flatten: true, 
          src: 'src/add-on/include/espeak-ng/src/windows/X64/Release/libespeak-ng.dll', 
          dest: 'dist/lib/win32/' 
        }]
      },

      'post-build-addon': {
        expand: true,
        flatten: true,
        src: 'build/Release/espeak_addon.node',
        dest: 'dist/lib/win32/',
      },

      'pre-compile-data': {
        cwd: 'src/add-on/include/espeak-ng',
        expand: true,
        src: [ 'dictsource/**', 'espeak-data/**', 'phsource/**' ],
        dest: 'dist/'
      }
    },

    eslint: {
      options: {
        config : '.eslintrc.json'
      },
      target : [ '_build/**/*.js', 'src/*.js' ]
    }
  })

  grunt.registerTask('default', [ 'lint', 'babel', 'build-addon', 'compile-data' ])

  grunt.registerTask('lint', [ 'eslint' ])

  grunt.registerTask('build-addon', [
    'clean:dist',
    'node-gyp:configure',
    'copy:pre-build-espeak',
    'build-espeak-ng',
    'copy:post-build-espeak',
    'node-gyp:build',
    'copy:post-build-addon',
    'clean:post-build-addon' ])

  grunt.registerTask('compile-data', [ 'copy:pre-compile-data', 'compile-espeak-data', 'clean:post-compile-data' ])

}
