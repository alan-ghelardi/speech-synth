const spawn = require('../libs/spawn-wrapper')

module.exports = (grunt) => {

  const spawnNodeGypOnCurrentPlatform = (command) => {
    if (process.platform === 'win32') {
      return spawn('cmd', [ '/c', 'node-gyp', command ])
    } else {
      throw new Error('Not implemented yet')
    }
  }

  grunt.registerTask('node-gyp', 'Runs node-gyp commands', function (command) {
    grunt.log.writeln(`Running the "${command}" command`)
    
    const done = this.async()
    const nodeGyp = spawnNodeGypOnCurrentPlatform(command)
    nodeGyp.on('exit', code => {
      if (code !== 0) {
        grunt.log.errorlns('The node-gyp command failed')
        done(false)
      } else {
        done()
      }
    })
  })
}
