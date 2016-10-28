import camelCase from './camel-case'
import espeak from './single-espeak'
import EspeakParameter from './espeak-parameter'
import Voice from './voice'

const speech = { 

  get voice() {
    const rawName = espeak.getVoice()
    return Voice.valueOf(rawName)
  },

  set voice(aVoice) {
    espeak.setVoice(aVoice.rawName)
  },

  speak(text){
    return new Promise((resolve, reject) => {
      espeak.speak(text, error => {
        if (error) {
          reject(error)
        } else {
          resolve()
        }
      })
    })
  },

  stop() {
    espeak.stop()   
  }

}

for (let parameter of EspeakParameter) {
  const identifier = parameter.value
  
  Object.defineProperty(speech, camelCase(parameter.name), {
    get : () => espeak.getParameter(identifier), 
    
    set : (value) => espeak.setParameter(identifier, value)
  })
}

export default speech
