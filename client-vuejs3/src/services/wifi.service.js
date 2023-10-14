import { baseUrl } from '~/utlis'

const nearWifi = async () => {
  const data = await fetch(baseUrl + '/nearWifi')
  const json = await data.json()
  return json
}
const getWifi = async () => {
  const data = await fetch(baseUrl + '/getWifi')
  const json = await data.json()
  return json
}

const setStaPASS = async password => {
  const data = await fetch(
    baseUrl +
      '/setStaPASS?' +
      new URLSearchParams({
        value: password
      })
  )
  const json = await data.json()
  return json
}
const setApSSID = async ssid => {
  const data = await fetch(
    baseUrl +
      '/setApSSID?' +
      new URLSearchParams({
        value: ssid
      })
  )
  const json = await data.json()
  return json
}

const setApPASS = async password => {
  const data = await fetch(
    baseUrl +
      '/setApPASS?' +
      new URLSearchParams({
        value: password
      })
  )
  const json = await data.json()
  return json
}
const setStaSSID = async ssid => {
  const data = await fetch(
    baseUrl +
      '/setStaSSID?' +
      new URLSearchParams({
        value: ssid
      })
  )
  const json = await data.json()
  return json
}
export default {
  nearWifi,
  getWifi,
  setStaPASS,
  setStaSSID,
  setApSSID,
  setApPASS
}
