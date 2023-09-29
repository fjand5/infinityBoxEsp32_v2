<script setup>
import { storeToRefs } from 'pinia';
import { useLedSelectedStore, useLedStateStore, useLiveTimeSelectedStore, useLedModeSelectedStore } from '../store';
import { ref, watch } from 'vue';
import { ledModeToString, ledModeToggle } from '../utlis';

const ledSelectedStore = useLedSelectedStore();
const liveTimeSelectedStore = useLiveTimeSelectedStore();
const ledModeSelectedStore = useLedModeSelectedStore();
const ledStateStore = useLedStateStore();
const { ledSelected } = storeToRefs(ledSelectedStore)
const { liveTimeSelected, adjOneByOne } = storeToRefs(liveTimeSelectedStore)
const { ledModeSelected } = storeToRefs(ledModeSelectedStore)
const { groups, selectedGroup } = storeToRefs(ledStateStore)
const bright = ref(0)
const liveTime = ref(0)
const ledMode = ref('LedMode_Normal')
// const calcInitBright = () => {
//   let tmp = 0
//   ledSelected.value.forEach((elm) => {
//     tmp = groups.value[elm.index.groupIndex]['data'][elm.index.stateIndex].bright[elm.port]
//   })
//   bright.value = tmp
//   return tmp
// }
watch(ledSelected, (n) => {
  let tmp = 0
  ledSelected.value.forEach((elm) => {
    tmp = groups.value[elm.index.groupIndex]['data'][elm.index.stateIndex].bright[elm.port]
  })
  bright.value = tmp
})
// const calcInitTime = () => {
//   liveTimeSelected.value.forEach((elm) => {
//     liveTime.value = groups.value[elm.groupIndex]['data'][elm.stateIndex].liveTime
//   })
//   return  liveTime.value
// }
watch(liveTimeSelected, (n) => {
  n.forEach((elm) => {
    liveTime.value = groups.value[elm.groupIndex]['data'][elm.stateIndex].liveTime
  })
})
const addTime = () => {

  let tmp = JSON.parse(JSON.stringify(groups.value))
  if (liveTimeSelectedStore.adjOneByOne) {
    liveTimeSelected.value.forEach((elm) => {
      tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime = tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime + 50

    })

  } else {

    liveTime.value = Number(liveTime.value) + 50
    if (liveTime.value > 900)
      liveTime.value = 900
    liveTimeSelected.value.forEach((elm) => {
      tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime = liveTime.value

    })
  }
  groups.value = JSON.parse(JSON.stringify(tmp))

}
const minusTime = () => {
  let tmp = JSON.parse(JSON.stringify(groups.value))

  if (liveTimeSelectedStore.adjOneByOne) {
    liveTimeSelected.value.forEach((elm) => {
      if (tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime > 50)
        tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime = tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime - 50

    })

  } else {


    liveTime.value = Number(liveTime.value) - 50
    if (liveTime.value < 50)
      liveTime.value = 50
    liveTimeSelected.value.forEach((elm) => {

      tmp[elm.groupIndex]['data'][elm.stateIndex].liveTime = liveTime.value

    })
  }
  groups.value = JSON.parse(JSON.stringify(tmp))

}

</script>

<template>
  <div class="fixed w-full bottom-0 h-fit">
    <div :class="ledSelected.length > 0 ? 'h-20' : 'h-0'"
      class="max-w-xs bottom-0 flex gap-4 items-center overflow-hidden px-2 w-full bg-led-100 transition-all duration-300">
      <span class="text-led-400 font-semibold text-lg  flex items-center">
        Độ sáng {{ bright }}:
      </span>
      <input :value="bright" @change="(e) => {
        const value = e.target.value
        ledSelected.forEach((elm) => {
          groups[elm.index.groupIndex]['data'][elm.index.stateIndex].bright[elm.port] = value

        })
      }" class="flex-grow accent-led-200 " type="range" min="0" max="255" />

    </div>
    <div :class="liveTimeSelected.length > 0 ? 'h-20' : 'h-0'"
      class="max-w-xs bottom-0  flex justify-center items-center gap-5 overflow-hidden px-5 w-full bg-led-100 transition-all duration-300">
      <span class="text-led-400 font-semibold text-lg  flex items-center">
        Thời gian:
      </span>
      <span v-if="!adjOneByOne" class="text-led-400 font-semibold text-lg ">{{ (liveTime /
        1000).toFixed(2) }}</span>
      <div class="flex flex-col">

        <span @click="() => addTime()" class="text-led-400 font-semibold text-lg cursor-pointer ">

          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor"
            class="w-6 h-6">
            <path stroke-linecap="round" stroke-linejoin="round" d="M4.5 15.75l7.5-7.5 7.5 7.5" />
          </svg>


        </span>
        <span @click="() => minusTime()" class="text-led-400 font-semibold text-lg  cursor-pointer ">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor"
            class="w-6 h-6">
            <path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-7.5 7.5-7.5-7.5" />
          </svg>

        </span>
      </div>

      <div class="flex flex-col">

<span @click="() => addTime()" class="text-led-400 font-semibold text-lg cursor-pointer ">

  <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor"
    class="w-6 h-6">
    <path stroke-linecap="round" stroke-linejoin="round" d="M4.5 15.75l7.5-7.5 7.5 7.5" />
  </svg>


</span>
<span @click="() => minusTime()" class="text-led-400 font-semibold text-lg  cursor-pointer ">
  <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor"
    class="w-6 h-6">
    <path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-7.5 7.5-7.5-7.5" />
  </svg>

</span>
</div>

    </div>
    <!-- <div :class="ledModeSelected.length > 0 ? 'h-20' : 'h-0'"
      class="max-w-xs bottom-0  flex justify-center items-center gap-5 overflow-hidden px-5 w-full bg-led-100 transition-all duration-300">
      <span class="text-led-400 font-semibold text-lg  flex items-center">
        Hiệu ứng:
      </span>
      <span @click="onClickLedMode" class="text-led-400 font-semibold text-lg w-14 cursor-pointer">{{
        ledModeToString(calcInitLedMode()) }}</span>

    </div> -->
  </div>
</template>

<style scoped></style>
