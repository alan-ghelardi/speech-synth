path = require 'path'
espeakFactory = module.exports

espeakFactory.newCompilerInstance = (dataPath) ->
  Espeak = getEspeak()
  new Espeak(dataPath, true)

getEspeak = ->
  if process.platform is 'win32'
    {Espeak} = require './win32/espeak_addon'
    Espeak
  else
    throw new Error('Not implemented yet')

espeakFactory.getCachedInstance = do ->
  espeakInstance = null
  return ->
    if not espeakInstance?
      Espeak = getEspeak()
      dataPath = path.resolve('.')
      espeakInstance = new Espeak(dataPath)
    espeakInstance
