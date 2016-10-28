
const matcher = /_(\w)/g

export default function(word) {
  return word.toLowerCase()
  .replace(matcher, (ignore, letter) => letter.toUpperCase())
}
