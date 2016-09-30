import espeak from './single-espeak'

const speech = Object.create(null)

speech.speak = (text) => {
  return new Promise((resolve, reject) => {
    espeak.speak(text, error => {
      if (error) {
        reject(error)
      } else {
        resolve()
      }
    })
  })
}

speech.stop = () => {
  espeak.stop()  
}

export default speech
