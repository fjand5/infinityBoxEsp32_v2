import baseUrl from './baseUrl'
const setDateTime = async dateTime => {
  const data = await fetch(
    baseUrl +
      '/setDateTime?' +
      new URLSearchParams({
        value: dateTime
      })
  )
  const json = await data.json()
  return json
}
export default {
  setDateTime,
}
