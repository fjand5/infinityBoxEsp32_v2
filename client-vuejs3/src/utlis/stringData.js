const listEffectName = [
  'EffectName_RunPaletteFace',
  'EffectName_RunPaletteSegment',
  'EffectName_OverflowSegment',
  'EffectName_OverflowFace',
  'EffectName_VUMeterSegment',
  'EffectName_ShowPaletteFace',
  'EffectName_VUMeterHalfSegment',
  'EffectName_StarSegment'
]
const listPaletteName = [
  'CloudColors_p',
  // 'LavaColors_p',
  'OceanColors_p',
  'ForestColors_p',
  'RainbowColors_p',
  'RainbowStripeColors_p',
  'PartyColors_p',
  'HeatColors_p',
  'Rainbow_gp'
]
const paletteNameToString = paletteName => {
  if (paletteName === 'CloudColors_p') {
    return 'Cloud Colors'
  }
  if (paletteName === 'LavaColors_p') {
    return 'Lava Colors'
  }
  if (paletteName === 'OceanColors_p') {
    return 'Ocean Colors'
  }
  if (paletteName === 'ForestColors_p') {
    return 'Forest Colors'
  }
  if (paletteName === 'RainbowColors_p') {
    return 'Rainbow Colors'
  }
  if (paletteName === 'RainbowStripeColors_p') {
    return 'Rainbow Stripe Colors'
  }
  if (paletteName === 'PartyColors_p') {
    return 'Party Colors'
  }
  if (paletteName === 'HeatColors_p') {
    return 'Heat Colors'
  }
  if (paletteName === 'Rainbow_gp') {
    return 'Rainbow'
  }
}
const stringToPaletteName = string => {
  if (string === 'Cloud Colors') {
    return 'CloudColors_p'
  }
  if (string === 'Lava Colors') {
    return 'LavaColors_p'
  }
  if (string === 'Ocean Colors') {
    return 'OceanColors_p'
  }
  if (string === 'Forest Colors') {
    return 'ForestColors_p'
  }
  if (string === 'Rainbow Colors') {
    return 'RainbowColors_p'
  }
  if (string === 'Rainbow Stripe Colors') {
    return 'RainbowStripeColors_p'
  }
  if (string === 'Party Colors') {
    return 'PartyColors_p'
  }
  if (string === 'Heat Colors') {
    return 'HeatColors_p'
  }
  if (string === 'Rainbow') {
    return 'Rainbow_gp'
  }
}
const effectNameToString = effectName => {
  if (effectName === 'EffectName_RunPaletteFace') {
    return 'Run palette Face'
  }
  if (effectName === 'EffectName_RunPaletteSegment') {
    return 'Run palette Segment'
  }
  if (effectName === 'EffectName_OverflowSegment') {
    return 'Overflow Segment'
  }
  if (effectName === 'EffectName_OverflowFace') {
    return 'Overflow Face'
  }
  if (effectName === 'EffectName_VUMeterSegment') {
    return 'VU metter Segment'
  }
  if (effectName === 'EffectName_ShowPaletteFace') {
    return 'Show Palette Face'
  }
  if (effectName === 'EffectName_VUMeterHalfSegment') {
    return 'VU Meter Half Segment'
  }
  if (effectName === 'EffectName_StarSegment') return 'Star Segment'
}
const stringToEffectName = string => {
  if (string === 'Run palette Face') {
    return 'EffectName_RunPaletteFace'
  }
  if (string === 'Run palette Segment') {
    return 'EffectName_RunPaletteSegment'
  }
  if (string === 'Overflow Segment') {
    return 'EffectName_OverflowSegment'
  }
  if (string === 'Overflow Face') {
    return 'EffectName_OverflowFace'
  }
  if (string === 'VU metter Segment') {
    return 'EffectName_VUMeterSegment'
  }
  if (string === 'Show Palette Face') {
    return 'EffectName_ShowPaletteFace'
  }
  if (string === 'VU Meter Half Segment') {
    return 'EffectName_VUMeterHalfSegment'
  }
  if (string === 'Star Segment') return 'EffectName_StarSegment'
}

export default {
  listEffectName,
  listPaletteName,
  effectNameToString,
  stringToEffectName,
  paletteNameToString,
  stringToPaletteName
}
