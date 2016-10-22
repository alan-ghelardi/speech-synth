
export default function(value) {
  return value.toUpperCase().replace(/[\s\-]+/g, '_')
}
