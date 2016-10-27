
const platform = process.platform === 'win32' ? 'win32' : 'unix'

const {Espeak} = require(`./lib/${platform}/espeak_addon`)

export default Espeak
  