import { baseUrl } from '~/utlis'

const getMicrophone = async () => {
  const data = await fetch(baseUrl + '/getMicrophone')
  const json = await data.json()
  return json
}

const setMicrophoneGain = async gain => {
  const data = await fetch(
    baseUrl +
      '/setMicrophoneGain?' +
      new URLSearchParams({
        value: gain
      })
  )
  const json = await data.json()
  return json
}
const setMicrophoneBeat = async beat => {
  const data = await fetch(
    baseUrl +
      '/setMicrophoneBeat?' +
      new URLSearchParams({
        value: beat
      })
  )
  const json = await data.json()
  return json

}
export default {
  getMicrophone,
  setMicrophoneGain,
  setMicrophoneBeat
}
