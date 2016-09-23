const path = require('path')

module.exports = (grunt) => {

  const compileData = (dataPath, done) => {
    const espeakFactory = require('../../dist/espeak-factory')
    grunt.log.writeln(`Using espeak data from ${dataPath}`)
    const espeak = espeakFactory.newCompilerInstance(dataPath)
    const dictSource = path.join(dataPath, 'dictsource', path.sep)
    grunt.log.writeln(`Using dictionary sources from ${dictSource}`)
    espeak.compileData(dictSource, (error) => {
      if (error) {
        grunt.log.errorlns('Failed to compile espeak data. See the details bellow:')
        grunt.log.errorlns(error)
        done(false)
      } else {
        done()
      }
    }  )
  }

  grunt.registerTask('compile-espeak-data', 'Compile Espeak\'s data such as intonation, phoneme and dictionary files', function() {
    const done = this.async()
    const dataPath = path.join(process.cwd(), 'dist')
    compileData(dataPath, done)
  })
}
