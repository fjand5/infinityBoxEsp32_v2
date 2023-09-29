<script setup>
import { storeToRefs } from 'pinia';
import { ref, watch } from 'vue';
import { DisplayApi } from '../api';
import { useDisplayStore, useMetaStore } from "../store";
import { chainedTypeList, chainedTypeToString } from '../utlis';
const displayStore = useDisplayStore()
const metaStore = useMetaStore()

const brightness = ref(undefined)
const autoBrightness = ref(false)
const chainedType = ref(undefined)
const screenType = ref(undefined)

watch(displayStore, async (n, o) => {
  brightness.value = displayStore.brightness
  chainedType.value = displayStore.chainedType
  autoBrightness.value = displayStore.autoBrightness
})
watch(metaStore, async (n, o) => {
  screenType.value = metaStore.meta.content.screen
})
watch(brightness, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await DisplayApi.setDisplayBrightness(n)
})

watch(chainedType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await DisplayApi.setDisplayChainedType(n)
})
watch(autoBrightness, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await DisplayApi.setAutoBrightness(n)
})
watch(screenType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await DisplayApi.setScreen(n)
  await metaStore.loadMetaData()

})
</script>

<template>
  <div class="w-full h-full  min-h-screen py-5 flex-col flex gap-5">
    <div class="flex gap-4 items-center">
      <label className="w-30 shrink-0" :htmlFor="uidTick">
        Độ sáng tự động:
      </label>
      <select id="chainedType" v-model="autoBrightness"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <option :value="true">Tự Động</option>
        <option :value="false">Thủ Công</option>
      </select>
    </div>
    <div v-if="autoBrightness==false" class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Độ sáng:
      </label>
      <input v-model="brightness" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="0" max="255"
        step="25" />
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" :htmlFor="uidTick">
        Bố trí:
      </label>
      <select id="chainedType" v-model="chainedType"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="displayChainedType in chainedTypeList">
          <option :value="displayChainedType">{{ chainedTypeToString(displayChainedType) }}</option>
        </template>
      </select>
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0" :htmlFor="uidTick">
        Kiểu:
      </label>
      <select id="chainedType" v-model="screenType"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <option value="Screen_Calendar">Đồng Hồ Vạn Niên</option>
        <option value="Screen_Text">Chạy Chữ</option>
      </select>
    </div>
  </div>
</template>

<style scoped></style>