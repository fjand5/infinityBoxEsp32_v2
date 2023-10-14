const rssiToPercent = (rssi) => {
  // rssi to Quality:
  let quality
  if (rssi <= -100) quality = 0
  else if (rssi >= -50) quality = 100
  else quality = 2 * (rssi + 100)

  // Quality to rssi:
  if (quality <= 0) rssi = -100
  else if (quality >= 100) rssi = -50
  else rssi = quality / 2 - 100
  console.log(quality)
  return quality
}
export default {
  rssiToPercent
}