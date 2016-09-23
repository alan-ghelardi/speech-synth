const {spawn} = require('child_process')
const _ = require('lodash')

module.exports = (command, args = [], options = {}) => {
  if(_.isPlainObject(args)) {
    options = args
    args = []
  }
  return spawnChildProcess(command, args, options)
}

const spawnChildProcess = (command, args, options) => {
  const normalizedArgs = normalizeOptions(options)
  args = args.concat(normalizedArgs)

  const childProcess = spawn(command, args)

  childProcess.stderr.pipe(process.stderr)
  childProcess.stdout.pipe(process.stdout)

  return childProcess
}

const normalizeOptions = (options) => {
  return _.chain(options)
  .mapKeys((value, key) => _.startsWith(key, '-') ? key : '--' + key)
  .toPairs()
  .flatten().value()
}
