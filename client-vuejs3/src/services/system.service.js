import { baseUrl } from '~/utlis'

const getSystem = async () => {
  const data = await fetch(baseUrl + '/getBox')
  const json = await data.json()
  return json
}

const setBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setBoxBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setAutoMode = async autoMode => {
  const data = await fetch(
    baseUrl +
      '/setAutoMode?' +
      new URLSearchParams({
        value: autoMode ? 'true' : 'false'
      })
  )
  const json = await data.json()
  return json
}
const setOnMicrophone = async onMicrophone => {
  const data = await fetch(
    baseUrl +
      '/setOnMicrophone?' +
      new URLSearchParams({
        value: onMicrophone ? 'true' : 'false'
      })
  )
  const json = await data.json()
  return json
}
const setEffectName = async effectName => {
  const data = await fetch(
    baseUrl +
      '/setEffectName?' +
      new URLSearchParams({
        value: effectName
      })
  )
  const json = await data.json()
  return json
}
const setEffectPalette = async paletteName => {
  const data = await fetch(
    baseUrl +
      '/setEffectPalette?' +
      new URLSearchParams({
        value: paletteName
      })
  )
  const json = await data.json()
  return json
}
const setTimeAutoChangeMode = async time => {
  const data = await fetch(
    baseUrl +
      '/setTimeAutoChangeMode?' +
      new URLSearchParams({
        value: time
      })
  )
  const json = await data.json()
  return json
}
const setStop = async stop => {
  const data = await fetch(
    baseUrl +
      '/setStop?' +
      new URLSearchParams({
        value: stop
      })
  )
  const json = await data.json()
  return json
}
const setPowerOn = async powerOn => {
  const data = await fetch(
    baseUrl +
      '/setPowerOn?' +
      new URLSearchParams({
        value: powerOn
      })
  )
  const json = await data.json()
  return json
}
const setNextEffect = async () => {
  const data = await fetch(baseUrl + '/setNextEffect')
  const json = await data.json()
  return json
}
const setPreviousEffect = async () => {
  const data = await fetch(baseUrl + '/setPreviousEffect')
  const json = await data.json()
  return json
}
export default {
  getSystem,
  setBrightness,
  setAutoMode,
  setOnMicrophone,
  setEffectName,
  setEffectPalette,
  setStop,
  setNextEffect,
  setPreviousEffect,
  setPowerOn,
  setTimeAutoChangeMode
}
