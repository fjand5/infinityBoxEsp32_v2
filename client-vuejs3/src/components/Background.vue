<script setup>
import { onMounted, reactive, ref, watch } from 'vue';
import { v4 as uuidv4 } from 'uuid';
import { BackgroundApi } from '../api'
import { backgroundEffectList, backgroundEffectToString,colorTypeList, colorTypeToString } from '../utlis'
import { ColorPicker } from 'vue-accessible-color-picker';

const uidBrightness = ref(undefined)
const uidTick = ref(undefined)
const brightness = ref(undefined)
const tick = ref(undefined)
const effect = ref(undefined)
const colorType = ref(undefined)
const color = ref(undefined)
const text = ref("")

onMounted(async () => {
  uidBrightness.value = uuidv4()
  uidTick.value = uuidv4()
  const data = await BackgroundApi.getBackground();
  brightness.value = data['brightness']
  effect.value = data['effect']
  text.value = data['text']
  colorType.value = data['colorType']
  color.value = data['color']
  tick.value = (100 - data['tick']) / 10
})
watch(brightness, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BackgroundApi.setBackgroundBrightness(n)
})
watch(tick, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BackgroundApi.setBackgroundTick(100 - n * 10)
})
watch(effect, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BackgroundApi.setBackgroundEffect(n)
})
watch(colorType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BackgroundApi.setBackgroudColorType(n)
})

const changeColor = async (data) => {
  let color = data.colors.hex
  color = color.replace("#", "")
  color = color.slice(0, -2)
  await BackgroundApi.setBackgroudColor(color)
}
const sendText = async () => {
  if (text.value.length > 2000) {
    useMessageStore().addMessage(
      `Tối đa 2000 ký tự`,
      'ERROR',
      4
    )
  }
  await BackgroundApi.setText(text.value)

}
</script>

<template>
  <div class="w-full h-full  min-h-screen py-5 flex-col flex gap-5">
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" :htmlFor="uidBrightness">
        Độ sáng:
      </label>
      <input v-model="brightness" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="0" max="255" step="25"
        :id="uidBrightness" />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" :htmlFor="uidTick">
        Tốc độ:
      </label>
      <input v-model="tick" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="1" max="10" step="1"
        :id="uidTick" />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" :htmlFor="uidTick">
        Hiệu ứng:
      </label>
      <select id="effect" v-model="effect"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="backgroundEffect in backgroundEffectList">
          <option :value="backgroundEffect">{{ backgroundEffectToString(backgroundEffect) }}</option>
        </template>
      </select>

    </div>
    <div v-if="effect === 'BackgroundEffect_RunText'" class="flex gap-2 items-center">
      <label className="w-20 shrink-0">
        Nội dung:
      </label>

      <textarea v-model="text"
        class="appearance-none border border-led-100 rounded w-full py-2 px-3 text-led-100 outline-none bg-led-400"
        type="text" placeholder=""></textarea>
      <button @click="sendText">Gửi</button>
    </div>

    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" :htmlFor="uidTick">
        Màu:
      </label>
      <select id="colorType" v-model="colorType"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="_colorType in colorTypeList">
          <option :value="_colorType">{{ colorTypeToString(_colorType) }}</option>
        </template>
      </select>

    </div>

    <div class="flex" v-if="colorType == 'ColorType_Static'">
      <ColorPicker :visible-formats="['rgb', 'hex']" default-format="rgb" @color-change="changeColor" alpha-channel="hide"
        :color="color" />
    </div>
  </div>
</template>

<style scoped></style>