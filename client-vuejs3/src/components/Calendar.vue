<script setup>
import { onMounted, ref, watch } from 'vue';
import { ColorPicker } from 'vue-accessible-color-picker';
import { CalendarApi } from '../api';
import { colorTypeList, colorTypeToString, calendarShowType3VList, calendarShowType2VList, calendarTypeToString, calendarFontList } from '../utlis';
import { useMetaStore, useDisplayStore, useMessageStore } from "../store";
import { storeToRefs } from 'pinia';

const metaStore = useMetaStore()
const { meta } = storeToRefs(metaStore)
const displayStore = useDisplayStore()

const calendarShowType = ref(undefined)
const brightness = ref(undefined)
const tick = ref(undefined)
const colorType = ref(undefined)
const typeList = ref([])
const color = ref("#ffffff")
const message = ref("")
const font = ref("")
const calendarData = ref()
onMounted(async () => {
  calendarData.value = await CalendarApi.getCalendar();
  brightness.value = calendarData.value['brightness']
  colorType.value = calendarData.value['colorType']
  color.value = '#' + calendarData.value['color']
  message.value = calendarData.value['message']
  font.value = calendarData.value['font']
  tick.value = (100 - calendarData.value['tick']) / 10
})
watch(displayStore, (n, o) => {
  if (n === undefined || o === undefined) return;
  if (displayStore.chainedType === "ChainedType_3V") {
    typeList.value = calendarShowType3VList
    calendarShowType.value = calendarData.value['showType3V']
  }
  else if (displayStore.chainedType === "ChainedType_2V") {
    typeList.value = calendarShowType2VList
    calendarShowType.value = calendarData.value['showType2V']
  }
})
watch(brightness, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await CalendarApi.setCalendarBrightness(n)
})
watch(colorType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await CalendarApi.setCalendarColorType(n)
})
watch(font, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await CalendarApi.setCalendarFont(n)
})
watch(tick, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await CalendarApi.setCalendarTick(100 - n * 10)
})
watch(calendarShowType, async (n, o) => {
  if (displayStore.chainedType === "ChainedType_3V") {
    CalendarApi.setCalendarShowType3V(n)
  }
  else if (displayStore.chainedType === "ChainedType_2V") {
    CalendarApi.setCalendarShowType2V(n)
  }
})
const changeColor = async (data) => {
  let color = data.colors.hex
  color = color.replace("#", "")
  color = color.slice(0, -2)
  await CalendarApi.setCalendarColor(color)
}
const sendMessage = async () => {
  if (message.value.length > 2000) {
    useMessageStore().addMessage(
      `Tối đa 2000 ký tự`,
      'ERROR',
      4
    )
  }
  await CalendarApi.setCalendarMessage(message.value)

}
watch(colorType, async (n, o) => {
  if (n === undefined || o === undefined) return;
  await CalendarApi.setCalendarColorType(n)
})
</script>

<template>
  <div class="w-full h-full  min-h-screen py-5 flex-col flex gap-5">


    <div v-if="displayStore.chainedType != 'ChainedType_3H' && displayStore.chainedType != 'ChainedType_1'"
      class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Kiểu:
      </label>
      <select id="effect" v-model="calendarShowType"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="calendarType in typeList">
          <option :value="calendarType">{{ calendarTypeToString(calendarType) }}</option>
        </template>
      </select>
    </div>
    <div v-if="calendarShowType === 'CalendarShowType3V_Digital_Top'" class="flex gap-2 items-center">
      <label className="w-20 shrink-0">
        Nội dung:
      </label>

      <textarea v-model="message"
        class="appearance-none border border-led-100 rounded w-full py-2 px-3 text-led-100 outline-none bg-led-400"
        type="text" placeholder=""></textarea>
      <button @click="sendMessage">Gửi</button>
    </div>
    <div v-if="calendarShowType === 'CalendarShowType3V_Digital_Top'" class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Font:
      </label>
      <select id="effect" v-model="font"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="calendarFont in calendarFontList">
          <option :value="calendarFont">{{ calendarFont }}</option>
        </template>
      </select>
    </div>
    <div class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Hiệu ứng:
      </label>
      <select id="effect" v-model="colorType"
        class="bg-led-400 appearance-none text-center border border-led-100 text-led-100 text-base rounded-lg w-full p-2.5">
        <template v-for="calendarColorType in colorTypeList">
          <option :value="calendarColorType">{{ colorTypeToString(calendarColorType) }}</option>
        </template>
      </select>
    </div>
    <div v-if="colorType != 'CalendarColorType_Static'" class="flex gap-4 items-center">
      <label className="w-20 shrink-0">
        Độ sáng:
      </label>
      <input v-model="brightness" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="0" max="255"
        step="25" />
    </div>
    <div class="flex gap-4 items-center" v-if="colorType != 'CalendarColorType_Static'">
      <label className="w-20 shrink-0">
        Tốc độ:
      </label>
      <input v-model="tick" type="range"
        className=" h-2 w-full shrink  cursor-pointer appearance-none rounded-md bg-led-200 " min="1" max="10" step="1" />
    </div>

    <div class="flex" v-if="colorType == 'ColorType_Static'">
      <ColorPicker :visible-formats="['rgb', 'hex']" default-format="rgb" @color-change="changeColor" alpha-channel="hide"
        :color="color" />
    </div>
  </div>
</template>

<style scoped></style>