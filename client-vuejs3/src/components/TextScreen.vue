<script setup>
import { onMounted, ref, watch } from 'vue';
import { TextScreenApi } from '../api';
import { fontList, colorTypeList, colorTypeToString, fontToString } from '../utlis';
import { useMessageStore } from "../store";
import IconClose from './icon/IconClose.vue';
import IconUp from './icon/IconUp.vue';
import IconDown from './icon/IconDown.vue';
import { ColorPicker } from 'vue-accessible-color-picker';


const brightness = ref(undefined)
const tick = ref(undefined)
const colorType = ref(undefined)
const color = ref("#ffffff")
const text = ref("")
const font = ref("")
const textScreenData = ref()
const yPosition = ref()

onMounted(async () => {
  textScreenData.value = await TextScreenApi.getScreenText();
  brightness.value = textScreenData.value['brightness']
  colorType.value = textScreenData.value['colorType']
  color.value = '#' + textScreenData.value['color']
  text.value = textScreenData.value['text']
  font.value = textScreenData.value['font']
  yPosition.value = textScreenData.value['yPosition']
  tick.value = (100 - textScreenData.value['tick']) / 10
})
watch(brightness, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await TextScreenApi.setTextBrightness(n)
})
watch(colorType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await TextScreenApi.setTextColorType(n)
})
watch(font, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await TextScreenApi.setFont(n)
  console.log(n)
})
watch(tick, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await TextScreenApi.setTextTick(100 - n * 10)
})
watch(yPosition, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await TextScreenApi.setYPosition(n)
})
const changeColor = async (data) => {
  let color = data.colors.hex
  color = color.replace("#", "")
  color = color.slice(0, -2)
  await TextScreenApi.setTextColor(color)
}
const sendText = async () => {
  if (text.value.length > 2000) {
    useMessageStore().addMessage(
      `Tối đa 2000 ký tự`,
      'ERROR',
      4
    )
  }
  await TextScreenApi.setText(text.value)

}
watch(colorType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await TextScreenApi.setTextColorType(n)
})
</script>

<template>
  <div class="w-full h-full  min-h-screen py-5 flex-col flex gap-5">
    <div class="flex gap-2 items-center">
      <label className="w-20 shrink-0">
        Nội dung:
      </label>

      <textarea v-model="text"
        class="appearance-none border border-led-100 rounded w-full py-2 px-3 text-led-100 outline-none bg-led-400"
        type="text" placeholder=""></textarea>
      <button @click="sendText">Gửi</button>
    </div>

    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Font:
      </label>
      <select id="effect" v-model="font"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="fontName in fontList">
          <option :value="fontName">{{ fontToString(fontName) }}</option>
        </template>
      </select>
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Vị Trí:
      </label>
      <div class="flex gap-10 justify-between">
        <button @click="() => yPosition--">
          <IconUp></IconUp>
        </button>
        <button @click="() => yPosition++">
          <IconDown></IconDown>
        </button>
      </div>

    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Hiệu ứng:
      </label>
      <select id="effect" v-model="colorType"
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
    <div v-if="colorType != 'ColorType_Static'" class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Độ sáng:
      </label>
      <input v-model="brightness" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="0" max="255"
        step="25" />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Tốc độ:
      </label>
      <input v-model="tick" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="1" max="10" step="1" />
    </div>
  </div>
</template>

<style scoped></style>