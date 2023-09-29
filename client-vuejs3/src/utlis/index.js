export const nextShadow = currentShadow => {
  if (currentShadow === 'Shadow_None') {
    return 'Shadow_BottomLeft'
  }
  if (currentShadow === 'Shadow_BottomLeft') {
    return 'Shadow_BottomRight'
  }
  if (currentShadow === 'Shadow_BottomRight') {
    return 'Shadow_TopLeft'
  }
  if (currentShadow === 'Shadow_TopLeft') {
    return 'Shadow_TopRight'
  }
  if (currentShadow === 'Shadow_TopRight') {
    return 'Shadow_None'
  }
  return 'Shadow_BottomRight'
}
export const shadowToString = shadow => {
  if (shadow === 'Shadow_None') {
    return 'Không'
  }
  if (shadow === 'Shadow_BottomLeft') {
    return 'Dưới Trái'
  }
  if (shadow === 'Shadow_BottomRight') {
    return 'Dưới Phải'
  }
  if (shadow === 'Shadow_TopLeft') {
    return 'Trên Trái'
  }
  if (shadow === 'Shadow_TopRight') {
    return 'Trên Phải'
  }
}
export const backgroundEffectList = [
  'BackgroundEffect_None',
  'BackgroundEffect_GrowCirle',
  'BackgroundEffect_RunCirle',
  'BackgroundEffect_RunTriangle',
  'BackgroundEffect_RunText',
  'BackgroundEffect_Arrow',
  'BackgroundEffect_Ball',
]
export const backgroundEffectToString = effect => {
  if (effect === 'BackgroundEffect_None') {
    return 'Không'
  }
  if (effect === 'BackgroundEffect_GrowCirle') {
    return 'Vòng Tròn Tỏa'
  }
  if (effect === 'BackgroundEffect_RunCirle') {
    return 'Vòng Tròn Chạy'
  }
  if (effect === 'BackgroundEffect_RunTriangle') {
    return 'Tam Giác Chạy'
  }
  if (effect === 'BackgroundEffect_RunText') {
    return 'Chạy Chữ'
  }
  if (effect === 'BackgroundEffect_Arrow') {
    return 'Mũi Tên'
  }
  if (effect === 'BackgroundEffect_Ball') {
    return 'Bóng Nảy'
  }
}

export const borderPaletteList = [
  "CloudColors_p",
  "LavaColors_p",
  "OceanColors_p",
  "ForestColors_p",
  "RainbowColors_p",
  "RainbowStripeColors_p",
  "PartyColors_p",
  "HeatColors_p",
  "Rainbow_gp"
]

export const borderPaletteToString = palette => {
  if(palette==="CloudColors_p"){
    return "Màu Mây"
  }
  if(palette==="LavaColors_p"){
    return "Màu Lava"
  }
  if(palette==="OceanColors_p"){
    return "Màu Đại Dương"
  }
  if(palette==="ForestColors_p"){
    return "Màu Rừng"
  }
  if(palette==="RainbowColors_p"){
    return "Cầu Vồng"
  }
  if(palette==="RainbowStripeColors_p"){
    return "Cầu Vòng Đoạn"
  }
  if(palette==="PartyColors_p"){
    return "Màu Sôi Động"
  }
  if(palette==="HeatColors_p"){
    return "Màu Ấm"
  }
  if(palette==="Rainbow_gp"){
    return "Cầu Vồng"
  }
}


export const colorTypeList = [
  "ColorType_Static",
  "ColorType_Rainbow",
  "ColorType_Square",
]
export const fontList = [
  "NotoSerif_10pt7b",
  "NotoSerif_11pt7b",
  "NotoSerif_12pt7b",
  "Roboto_Medium10pt7b",
  "Roboto_Medium11pt7b",
  "Roboto_Medium12pt7b",
  "Roboto_Medium13pt7b",
]

export const colorTypeToString = colorType => {
  if(colorType==="ColorType_Static"){
    return "Màu Tĩnh"
  }
  if(colorType==="ColorType_Rainbow"){
    return "Cầu Vồng"
  }
  if(colorType==="ColorType_Square"){
    return "Chạy Hình Vuông"
  }
}
export const fontToString = font => {
  if(font==="NotoSerif_10pt7b"){
    return "Có Chân 10"
  }
  if(font==="NotoSerif_11pt7b"){
    return "Có Chân 11"
  }
  if(font==="NotoSerif_12pt7b"){
    return "Có Chân 12"
  }
  if(font==="Roboto_Medium10pt7b"){
    return "Không Chân 10"
  }
  if(font==="Roboto_Medium11pt7b"){
    return "Không Chân 11"
  }
  if(font==="Roboto_Medium12pt7b"){
    return "Không Chân 12"
  }
  if(font==="Roboto_Medium13pt7b"){
    return "Không Chân 13"
  }
  
}

export const chainedTypeList = [
  'ChainedType_1',
  'ChainedType_2V',
  'ChainedType_2H',
  'ChainedType_3V',
  'ChainedType_3H'
]
export const chainedTypeToString = chainedType => {
  if(chainedType==="ChainedType_1"){
    return "Một Tấm"
  }
  if(chainedType==="ChainedType_2V"){
    return "Hai Tấm Đứng"
  }
  if(chainedType==="ChainedType_2H"){
    return "Hai Tấm Ngang"
  }
  if(chainedType==="ChainedType_3V"){
    return "Ba Tấm Đứng"
  }
  if(chainedType==="ChainedType_3H"){
    return "Ba Tấm Ngang"
  }
}
export const calendarTypeToString = calendarType => {
  if(
    calendarType==="CalendarShowType3V_Analog"||
    calendarType==="CalendarShowType2V_Analog"
  
  ){
    return "Đồng Hồ Kim"
  }
  if(
    calendarType==="CalendarShowType3V_Digital_Top"||
    calendarType==="CalendarShowType2V_Digital_Top"
  
  ){
    return "Đồng Hồ Số"
  }
}



export const calendarShowType3VList = [
 
  "CalendarShowType3V_Analog",
  "CalendarShowType3V_Digital_Top",
]
export const calendarShowType2VList = [

  "CalendarShowType2V_Analog",
  "CalendarShowType2V_Digital_Top",
]
export const calendarFontList = [

  "NotoSerif",
  "Roboto_Bold",
]
