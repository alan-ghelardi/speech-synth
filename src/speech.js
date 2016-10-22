import espeak from './single-espeak'
import Voice from './voice'

const speech = { 

  get voice() {
    const rawName = espeak.voice()
    return Voice.valueOf(rawName)
  },

  set voice(aVoice) {
    espeak.voice(aVoice.rawName)
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

export default speech
