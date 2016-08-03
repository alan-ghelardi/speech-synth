path = require 'path'
spawn = require '../libs/spawn-wrapper'

module.exports = (grunt) ->

  buildOnWindows = (done) ->
    vsProjectFile = path.join(process.cwd(), 'src', 'add-on', 'include', 'espeak-ng', 'src', 'windows', 'libespeak-ng.vcxproj')
    args = [ vsProjectFile, '/Property:Configuration=Release', '/Property:Platform=X64' ]
    msbuild = spawn('msbuild', args)
    msbuild.on('exit', (code) ->
      if code isnt 0
        grunt.log.errorlns('Failed to compile espeak-ng project')
        done(false)
      else
        done())

  grunt.registerTask('build-espeak-ng', 'Builds the espeak-ng project', ->
    done = @async()
    buildOnWindows(done))
