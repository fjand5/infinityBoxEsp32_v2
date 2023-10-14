import baseUrl from './baseUrl'
const setDisplayBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setDisplayBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setDisplayChainedType = async chainedType => {
  const data = await fetch(
    baseUrl +
      '/setDisplayChainedType?' +
      new URLSearchParams({
        value: chainedType
      })
  )
  const json = await data.json()
  return json
}
const setScreen = async chainedType => {
  const data = await fetch(
    baseUrl +
      '/setScreen?' +
      new URLSearchParams({
        value: chainedType
      })
  )
  const json = await data.json()
  return json
}
const setAutoBrightness = async autoBrightness => {
  const data = await fetch(
    baseUrl +
      '/setAutoBrightness?' +
      new URLSearchParams({
        value: autoBrightness
      })
  )
  const json = await data.json()
  return json
}
const getDisplay = async () => {
  const data = await fetch(baseUrl + '/getDisplay')
  const json = await data.json()
  return json
}
export default {
  setDisplayBrightness,
  getDisplay,
  setDisplayChainedType,
  setScreen,
  setAutoBrightness
}
