import baseUrl from './baseUrl';
const setShadow = async (shadow) => {
  const data =  await fetch(
    baseUrl +
      '/setShadow?'
      +new URLSearchParams({
        value: shadow
      })
  )
  const json = await data.json()
  return json
}
const getContent = async ()=>{
  const data = await fetch(
    baseUrl +
      '/getContent')
  const json = await data.json()
  return json
}
export default {getContent,setShadow}