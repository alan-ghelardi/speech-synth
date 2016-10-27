import Enum from 'enumerations'

/**
 * Maps the values of the enum `espeak_PARAMETER`, declared in the speak_lib.h.
 * 
 * This module is intended for internal use only.
 */
class EspeakParameter extends Enum {
  
}

EspeakParameter.values({
  RATE : {value: 1}
}, {
  VOLUME : {value: 2} 
}, {
  PITCH : {value : 3}
}, {
  PUNCTUATION : {value : 5}
}, {
  CAPITALS : {value : 6}
}, {
  WORD_GAP : {value : 7}
})

export default EspeakParameter
