<script setup>
import { onMounted, reactive, ref, watch } from 'vue';
import { v4 as uuidv4 } from 'uuid';
import { BorderApi } from '../api'
import { borderPaletteList, borderPaletteToString } from '../utlis'

const brightness = ref(undefined)
const tick = ref(undefined)
const palette = ref(undefined)
const width = ref(undefined)
onMounted(async () => {
  const data = await BorderApi.getBorder();
  brightness.value = data['brightness']
  palette.value = data['palette']
  width.value = data['width']
  tick.value = (100 - data['tick']) / 10
})
watch(brightness, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BorderApi.setBorderBrightness(n)
})
watch(tick, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BorderApi.setBorderTick(100 - n * 10)
})
watch(palette, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BorderApi.setBorderPalette(n)
})
watch(width, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await BorderApi.setBorderWidth(n)
})
</script>

<template>
  <div class="w-full h-full  min-h-screen py-5 flex-col flex gap-5">
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Độ sáng:
      </label>
      <input v-model="brightness" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="0" max="255" step="25"
         />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Tốc độ:
      </label>
      <input v-model="tick" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="1" max="10" step="1"
      />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" >
        Độ rộng:
      </label>
      <input v-model="width" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="1" max="10" step="1"
        />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Hiệu ứng:
      </label>
      <select id="palette"
      v-model="palette"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="borderPalette in borderPaletteList">
          <option  :value="borderPalette">{{ borderPaletteToString(borderPalette) }}</option>
        </template>
      </select>
    </div>
  </div>
</template>

<style scoped></style>