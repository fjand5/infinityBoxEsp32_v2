import baseUrl from './baseUrl'
const setBorderBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setBorderBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setBorderTick = async tick => {
  const data = await fetch(
    baseUrl +
      '/setBorderTick?' +
      new URLSearchParams({
        value: tick
      })
  )
  const json = await data.json()
  return json
}
const getBorder = async () => {
  const data = await fetch(baseUrl + '/getBorder')
  const json = await data.json()
  return json
}
const setBorderPalette = async (palette) => {
  const data = await fetch(
    baseUrl +
      '/setBorderPalette?' +
      new URLSearchParams({
        value: palette
      })
  )
  const json = await data.json()
  return json
}
const setBorderWidth = async (width) => {
  const data = await fetch(
    baseUrl +
      '/setBorderWidth?' +
      new URLSearchParams({
        value: width
      })
  )
  const json = await data.json()
  return json
}
export default {
  getBorder,
  setBorderPalette,
  setBorderBrightness,
  setBorderTick,
  setBorderWidth
}
