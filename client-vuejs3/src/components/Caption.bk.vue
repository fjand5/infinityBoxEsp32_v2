<script setup>
import { storeToRefs } from "pinia";
import { useLiveTimeSelectedStore, useLedStateStore, useLedSelectedStore, useLedModeSelectedStore } from "../store";
const ledStateStore = useLedStateStore()
const { groups, selectedGroup } = storeToRefs(ledStateStore)

const selectAllLiveTime = () => {
  let indexList = []
  groups.value[selectedGroup.value]['data'].forEach((elm, index) => {
    if (!elm?.repeat) {
      indexList.push({ groupIndex: selectedGroup.value, stateIndex: index })
    }
  })
  useLiveTimeSelectedStore().toggleSelectAll(indexList)
  useLedSelectedStore().clearSelected()
  useLedModeSelectedStore().clearSelected()
}
const stateLedStyle = () => {
  let numOfPort = groups.value[selectedGroup.value]?.['ports'].length
  if (numOfPort <= 4)
    return {
      width: '129px'
    }
  if (numOfPort == 5)
    return {
      width: '120px'
    }
  if (numOfPort == 6)
    return {
      width: '128px'
    }
  if (numOfPort == 7)
    return {
      width: '155px'
    }
  if (numOfPort == 8)
    return {
      width: '146px'
    }
}
const speedStyle = () => {
  let numOfPort = groups.value[selectedGroup.value]?.['ports'].length
  if (numOfPort <= 4)
    return {
      width: '65px'
    }
  if (numOfPort == 5)
    return {
      width: '65px'
    }
  if (numOfPort == 6)
    return {
      width: '60px'
    }
  if (numOfPort == 7)
    return {
      width: '60px'
    }
  if (numOfPort == 8)
    return {
      width: '57px'
    }
}
</script>

<template>
  <div class="w-full h-[1px] bg-led-100"></div>

  <div class="w-full flex h-8 justify-start gap-1 px-1 bg-led-400">

    <h2 class="w-[50px] text-center flex justify-start items-center">TT</h2>
    <h2 class="text-center flex justify-center items-center" :style="stateLedStyle()">Trạng thái led</h2>
    <h2 @click="()=>selectAllLiveTime()" class=" cursor-pointer flex justify-center items-center" :style="speedStyle()">T.Độ
    </h2>

    <h2  class="w-fit flex justify-start items-center">Dịu</h2>
  </div>
  <div class="w-full h-[1px] bg-led-100 mb-2"></div>
</template>

<style scoped></style>
