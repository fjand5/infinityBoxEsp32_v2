import baseUrl from './baseUrl'
const setTextBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setTextBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setTextTick = async tick => {
  const data = await fetch(
    baseUrl +
      '/setTextTick?' +
      new URLSearchParams({
        value: tick
      })
  )
  const json = await data.json()
  return json
}
const setText = async text => {
  const data = await fetch(
    baseUrl +
      '/setText?' +
      new URLSearchParams({
        value: text
      })
  )
  const json = await data.json()
  return json
}
const getScreenText = async () => {
  const data = await fetch(baseUrl + '/getScreenText')
  const json = await data.json()
  return json
}
const setFont = async font => {
  const data = await fetch(
    baseUrl +
      '/setFont?' +
      new URLSearchParams({
        value: font
      })
  )
  const json = await data.json()
  return json
}
const setYPosition = async yPosition => {
  const data = await fetch(
    baseUrl +
      '/setYPosition?' +
      new URLSearchParams({
        value: yPosition
      })
  )
  const json = await data.json()
  return json
}
const setTextColorType = async colorType => {
  const data = await fetch(
    baseUrl +
      '/setTextColorType?' +
      new URLSearchParams({
        value: colorType
      })
  )
  const json = await data.json()
  return json
}
const setTextColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setTextColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
export default {
  setTextBrightness,
  setTextTick,
  setText,
  getScreenText,
  setFont,
  setYPosition,
  setTextColorType,
  setTextColor
}
