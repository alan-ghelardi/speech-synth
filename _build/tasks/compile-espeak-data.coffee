path = require 'path'

module.exports = (grunt) ->

  compileData = (dataPath, done) ->
    espeakFactory = require '../../dist/espeak-factory'
    grunt.log.writeln("Using espeak data from #{dataPath}")
    espeak = espeakFactory.newCompilerInstance(dataPath)
    dictSource = path.join(dataPath, 'dictsource', path.sep)
    grunt.log.writeln("Using dictionary sources from #{dictSource}")
    espeak.compileData(dictSource, (error) ->
      if error?
        grunt.log.errorlns('Failed to compile espeak data. See the details bellow:')
        grunt.log.errorlns(error)
        done(false)
      else
        done())

  grunt.registerTask('compile-espeak-data', 'Compile Espeak\'s data such as intonation, phoneme and dictionary files', ->
    grunt.task.requires('coffee')
    done = @async()
    dataPath = path.join(process.cwd(), 'dist')
    compileData(dataPath, done))
