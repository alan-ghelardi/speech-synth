const path = require('path')
const spawn = require('../libs/spawn-wrapper')

module.exports = (grunt) => {

  const buildOnWindows = (done) => {
    const vsProjectFile = path.join(process.cwd(), 'src', 'cpp', 'include', 'espeak-ng', 'src', 'windows', 'libespeak-ng.vcxproj')
    const args = [ vsProjectFile, '/Property:Configuration=Release', '/Property:Platform=X64' ]
    const msbuild = spawn('msbuild', args)
    msbuild.on('exit', code => {
      if (code !== 0) {
        grunt.log.errorlns('Failed to compile espeak-ng project')
        done(false)
      } else {
        done()
      }
    }  )
  }

  grunt.registerTask('build-espeak-ng', 'Builds the espeak-ng project', function() {
    const done = this.async()
    buildOnWindows(done)
  })
}
