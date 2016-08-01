spawn = require '../libs/spawn-wrapper'

module.exports = (grunt) ->

  spawnNodeGypOnCurrentPlatform = (command) ->
    if process.platform is 'win32'
      spawn('cmd', [ '/c', 'node-gyp', command ])
    else
      throw new Error('Not implemented yet')
  
  grunt.registerTask('node-gyp', 'Runs node-gyp commands', (command) ->
    grunt.log.writeln("Running the `#{command}` command")
    
    done = @async()
    nodeGyp = spawnNodeGypOnCurrentPlatform(command)
    nodeGyp.on('exit', (code) ->
      if code isnt 0
        grunt.log.errorlns('The node-gyp command failed')
        done(false)
      else
        done()))
