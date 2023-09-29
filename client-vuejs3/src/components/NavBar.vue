<script setup>
import { ref, watch } from 'vue';
import { useMetaStore } from "../store";

import { onClickOutside } from '@vueuse/core';
import { storeToRefs } from 'pinia';
import { nextShadow, shadowToString } from '../utlis';
import Help from './Help.vue';
import WifiInfo from './WifiInfo.vue';
import IconClose from './icon/IconClose.vue';
import IconMenu from './icon/IconMenu.vue';
import ScanWifi from './ScanWifi.vue';


const metaStore = useMetaStore()
const { meta } = storeToRefs(metaStore)

const showMenu = ref(false)
const target = ref(null)
const showWifiInfoModal = ref(false)
const showScanWifiModal = ref(false)
const showGroupManagerModal = ref(false)
const showHelp = ref(false)

onClickOutside(target, () => showMenu.value = false)

watch(showMenu, async (n) => {
  // const json = await ContentApi.getContent();
  // shadow.value = json["shadow"]
  // console.log(json)
  // if (n) {
  //   ledMetaStateStore.loadLedMetaData()
  // }
})
const changeShadow = async () => {
  metaStore.commitShadow(nextShadow(meta.value.content["shadow"]))

}
</script>

<template>
  <Help :show="showHelp" @onClose="() => showHelp = false" />
  <div ref="target"
    class="h-fit min-h-[56px] relative bg-led-100 px-2 py-2 shadow-2xl w-full pointer-events-none flex flex-col  gap-3 justify-start transition-all duration-500 text-led-400 ">
    <span class="mx-auto mt-1 transition-all overflow-hidden h-fit">
      {{ meta.wifi["ApSSID"] }}
    </span>
    <ul class=" pointer-events-auto transition-all overflow-hidden flex flex-col justify-around items-center"
      :class="showMenu ? 'h-44' : 'h-0'">
      <li class=" w-full  flex flex-col items-center gap-1 px-2 ">
        <div class="flex gap-1 border-led-400  border-b-[1px] p-1 cursor-pointer  select-none">
          <span cl>Đổ bóng: </span>
          <div class=" flex gap-2">
            <span class="cursor-pointer" @click="changeShadow">
              {{ shadowToString(meta.content["shadow"]) }}
            </span>
          </div>
        </div>
      </li>
      <li @click="() => {

        showWifiInfoModal = true
        showMenu = false
      }" class="border-led-400  border-b-[1px] p-1 cursor-pointer  select-none">
        Đổi Thông Tin WIFI
      </li>
      <li @click="() => {

        showScanWifiModal = true
        showMenu = false
      }" class="border-led-400  border-b-[1px] p-1 cursor-pointer  select-none">
        Dò Wifi
      </li>
      <li @click="() => showHelp = true" class="border-led-400  border-b-[1px] p-1 cursor-pointer  select-none">
        Hướng Dẫn
      </li>

    </ul>
    <button @click="() => { showMenu = !showMenu }"
      class="outline-none  select-none rounded-sm border-led-400 border-[1px] absolute left-2 top-3 pointer-events-auto h-7 w-7 bg-led-100 flex justify-center items-center">

      <IconClose v-if="showMenu" />
      <IconMenu v-else></IconMenu>

    </button>
  </div>
  <WifiInfo :show="showWifiInfoModal" @onClose="() => { showWifiInfoModal = false }"></WifiInfo>
  <ScanWifi :show="showScanWifiModal" @onClose="() => { showScanWifiModal = false }"></ScanWifi>


  <GroupManager :show="showGroupManagerModal" @onClose="() => { showGroupManagerModal = false }" />
</template>

<style scoped></style>
