import { gzip } from 'zlib'
import fs from 'fs'

let index_html = ''
let index_html_length = 0

let app_js = ''
let app_js_length = 0
let index_css = ''
let index_css_length = 0
function convertToHex (data) {
  let value = '0x'
  let hexString = data
  for (let i = 0; i < hexString.length; i++) {
    value += hexString[i]
    if (i % 2 == 1 && i < hexString.length - 1) value += ',0x'
  }

  return {
    newData: value,
    length: hexString.length / 2
  }
}
let promises = []
console.log('Đang đọc file')
promises.push(
  fs.promises.readFile('./dist/index.html').then(data => {
    gzip(data, (err, compressed) => {
      let { newData, length } = convertToHex(compressed.toString('hex'))
      index_html = newData
      index_html_length = length
      return Promise.resolve()
    })
  })
)
promises.push(
  fs.promises.readFile('./dist/js/app.js').then(data => {
    gzip(data, (err, compressed) => {
      let { newData, length } = convertToHex(compressed.toString('hex'))
      app_js = newData
      app_js_length = length
      return Promise.resolve()
    })
  })
)
promises.push(
  fs.promises.readFile('./dist/css/index.css').then(data => {
    gzip(data, (err, compressed) => {
      let { newData, length } = convertToHex(compressed.toString('hex'))
      index_css = newData
      index_css_length = length
      return Promise.resolve()
    })
  })
)
const copyToDist = () => {
  let content = `
      #pragma once
      #include <pgmspace.h>
      static const char app_js[] PROGMEM = {${app_js}};
      static const long app_js_length = ${app_js_length};
      static const char index_css[] PROGMEM = {${index_css}};
      static const long index_css_length = ${index_css_length};
      static const char index_html[] PROGMEM = {${index_html}};
      static const long index_html_length = ${index_html_length};
      `
  console.log('Đang ghi file', content)

  fs.writeFile('../src/webserver/dist.h', content, 'utf8', async () => {
    console.log('Hoàn tất')
  })
}
// Promise.all(promises).then(copyToDist)
setTimeout(()=>{
    copyToDist()
},1000)
