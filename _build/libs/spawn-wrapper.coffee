{spawn} = require 'child_process'
_ = require 'lodash'

module.exports = (command, args = [], options = {}) ->
  if _.isPlainObject(args)
    options = args
    args = []

  spawnChildProcess(command, args, options)

spawnChildProcess = (command, args, options) ->
  normalizedArgs = normalizeOptions(options)
  args = args.concat(normalizedArgs)

  childProcess = spawn(command, args)

  childProcess.stderr.pipe(process.stderr)
  childProcess.stdout.pipe(process.stdout)

  childProcess

normalizeOptions = (options) ->
  _.chain(options)
  .mapKeys((value, key) -> if _.startsWith(key, '-') then key else '--' + key)
  .toPairs()
  .flatten().value()
