import baseUrl from './baseUrl'

const getWifi = async () => {
  const wifiData = await fetch(baseUrl + '/getWifi')
  const wifiJson = await wifiData.json()
  return wifiJson
}
const nearWifi = async () => {
  const wifiData = await fetch(baseUrl + '/nearWifi')
  const wifiJson = await wifiData.json()
  return wifiJson
}
const setApSSID = async apSSID => {
  const apSSIDData = await fetch(
    baseUrl +
      '/setApSSID?' +
      new URLSearchParams({
        value: apSSID
      })
  )
  const apSSIDJson = await apSSIDData.json()
  return apSSIDJson
}
const setApPASS = async apPASS => {
  const apPASSData = await fetch(
    baseUrl +
      '/setApPASS?' +
      new URLSearchParams({
        value: apPASS
      })
  )
  const apPASSJson = await apPASSData.json()
  return apPASSJson
}
const setStaSSID = async StaSSID => {
  const staSSIDData = await fetch(
    baseUrl +
      '/setStaSSID?' +
      new URLSearchParams({
        value: StaSSID
      })
  )
  const staSSIDJson = await staSSIDData.json()
  return staSSIDJson
}
const setStaPASS = async staPASS => {
  const staPASSData = await fetch(
    baseUrl +
      '/setStaPASS?' +
      new URLSearchParams({
        value: staPASS
      })
  )
  const staPASSJson = await staPASSData.json()
  return staPASSJson
}
export default {
  getWifi,
  setApSSID,
  setApPASS,
  setStaSSID,
  setStaPASS,
  nearWifi
}
