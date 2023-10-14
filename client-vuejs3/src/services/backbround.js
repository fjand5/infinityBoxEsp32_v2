import baseUrl from './baseUrl'
const setBackgroundBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setBackgroundBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setBackgroundTick = async tick => {
  const data = await fetch(
    baseUrl +
      '/setBackgroundTick?' +
      new URLSearchParams({
        value: tick
      })
  )
  const json = await data.json()
  return json
}
const getBackground = async () => {
  const data = await fetch(baseUrl + '/getBackground')
  const json = await data.json()
  return json
}
const setBackgroundEffect = async (effect) => {
  const data = await fetch(
    baseUrl +
      '/setBackgroundEffect?' +
      new URLSearchParams({
        value: effect
      })
  )
  const json = await data.json()
  return json
}

const setText = async text => {
  const data = await fetch(
    baseUrl +
      '/setBackgroundText?' +
      new URLSearchParams({
        value: text
      })
  )
  const json = await data.json()
  return json
}
const setBackgroudColorType = async color => {
  const data = await fetch(
    baseUrl +
      '/setBackgroudColorType?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
const setBackgroudColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setBackgroudColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
export default {
  getBackground,
  setBackgroundEffect,
  setBackgroundBrightness,
  setBackgroundTick,
  setBackgroudColorType,
  setBackgroudColor,
  setText
}
