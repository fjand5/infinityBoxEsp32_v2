import baseUrl from './baseUrl'
const setCalendarBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setCalendarBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setCalendarTick = async tick => {
  const data = await fetch(
    baseUrl +
      '/setCalendarTick?' +
      new URLSearchParams({
        value: tick
      })
  )
  const json = await data.json()
  return json
}
const setCalendarColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setCalendarColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
const getCalendar = async () => {
  const data = await fetch(baseUrl + '/getCalendar')
  const json = await data.json()
  return json
}
const setCalendarColorType = async (colorType) => {
  const data = await fetch(
    baseUrl +
      '/setCalendarColorType?' +
      new URLSearchParams({
        value: colorType
      })
  )
  const json = await data.json()
  return json
}
const setCalendarShowType3V = async (calendarType) => {
  const data = await fetch(
    baseUrl +
      '/setCalendarShowType3V?' +
      new URLSearchParams({
        value: calendarType
      })
  )
  const json = await data.json()
  return json
}
const setCalendarShowType2V = async (calendarType) => {
  const data = await fetch(
    baseUrl +
      '/setCalendarShowType2V?' +
      new URLSearchParams({
        value: calendarType
      })
  )
  const json = await data.json()
  return json
}
const setCalendarMessage = async (message) => {
  const data = await fetch(
    baseUrl +
      '/setCalendarMessage?' +
      new URLSearchParams({
        value: message
      })
  )
  const json = await data.json()
  return json
}
const setCalendarFont = async (font) => {
  const data = await fetch(
    baseUrl +
      '/setCalendarFont?' +
      new URLSearchParams({
        value: font
      })
  )
  const json = await data.json()
  return json
}
export default {
  getCalendar,
  setCalendarColorType,
  setCalendarBrightness,
  setCalendarTick,
  setCalendarColor,
  setCalendarShowType3V,
  setCalendarShowType2V,
  setCalendarMessage,
  setCalendarFont
}
