import Enum from 'enumerations'
import espeak from './single-espeak'
import upperSnakeCase from './upper-snake-case'

const voiceDeclarations = espeak.getAllVoices().map(voice => {
  return {
    [upperSnakeCase(voice)] : {rawName: voice}
  }
})

class Voice extends Enum {
  
  toString() {
    return this.rawName
  }
  
}

Voice.values(...voiceDeclarations)

export default Voice
