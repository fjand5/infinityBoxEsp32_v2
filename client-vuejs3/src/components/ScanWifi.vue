<script setup>
import IconEye from './icon/IconEye.vue';
import IconEyeSlash from './icon/IconEyeSlash.vue';
import IconLoading from './icon/IconLoading.vue';

import { useMessageStore, useMetaStore } from "../store";


import Dialog from './Dialog.vue';
import { onMounted, ref, watch } from 'vue';
import { storeToRefs } from 'pinia';
import IconClose from './icon/IconClose.vue';
import { MetaApi } from '../api';
const metaStore = useMetaStore()
const { meta } = storeToRefs(metaStore)
const emit = defineEmits(["onClose"]);

const props = defineProps(['show'])

const currentWifiName = ref('')
const wifiName = ref('')
const password = ref('')
const listWifi = ref([])
const showPassword = ref(false)
const passwordError = ref()

const listWifiOrdered = ref([])
watch(() => props.show, async (n, o) => {
  if (n === true) {
    listWifi.value = await MetaApi.nearWifi()
    currentWifiName.value = meta.value.wifi['StaSSID']
  }

})
watch(listWifi, async (n, o) => {
  if (n != []) {
    const seen = {};

    const filtered = n.filter((item) => {
      return seen.hasOwnProperty(item.ssid) ? false : (seen[item.ssid] = true);

    })
    listWifiOrdered.value = filtered.sort((a, b) => b.rssi - a.rssi)
  }

})
const onClose = () => {
  if (wifiName.value != '')
    wifiName.value = ''
  else
    emit('onClose')
}
const submitWifiInfo = async () => {
  if (password.value.length < 7) {
    passwordError.value = "Mật khẩu phải hơn 8 ký tự"
    return
  }
  if (password.value.length > 15) {
    passwordError.value = "Mật khẩu phải ít hơn 16 ký tự"
    return
  }
  passwordError.value = false
  await metaStore.commitStaSSID(wifiName.value)
  await metaStore.commitStaPASS(password.value)
  useMessageStore().addMessage(
    `Hoàn Thành`,
    'SUCCESS',
    3
  )
  currentWifiName.value = wifiName.value
  wifiName.value = ''
  emit('onClose')
}
</script>

<template>
  <Dialog :show="props.show">

    <template v-slot:header>
      <div class="flex w-full relative">

        <span class="absolute bottom-[50%] right-[50%] translate-x-[50%] translate-y-[50%]">
          Danh sách Wifi

        </span>
        <IconClose @click="() => onClose()" class="ml-auto" />
      </div>
    </template>

    <template v-slot:content>
      <div v-if="wifiName != ''"
        class="flex px-5 py-10 flex-col justify-start bg-led-400 opacity-95 w-full h-full absolute left-0 top-[56px] ">

        <div class="flex-col flex gap-5 ">
          <label class=" text-led-100 text-lg text-center" for="password">
            Mật khẩu Cho <span class="font-bold">{{ wifiName }}</span>
          </label>
          <span v-if="passwordError" class="flex text-led-500 font-normal">{{ passwordError }}</span>

          <div class="flex items-center gap-2  border border-led-100 rounded w-full py-2 px-3">

            <input class="appearance-none text-led-100 outline-none bg-led-400 w-full" id="password"
              :type="showPassword ? 'text' : 'password'" v-model="password" placeholder="Mật khẩu">
            <div class="">

              <IconEyeSlash v-if="showPassword" @click="() => showPassword = false" />
              <IconEye v-else @click="() => showPassword = true" />
            </div>
          </div>
          <div class="flex justify-between">
            <button @click="() => wifiName = ''">Quay Lại</button>
            <button @click="submitWifiInfo">OK</button>
          </div>
        </div>
      </div>
      <div class="flex justify-center py-5 h-full overflow-scroll">


        <div v-if="listWifi.length === 0" class="flex flex-col items-center">
          <span>Đang dò wifi xung quanh</span>
          <div>

            <IconLoading></IconLoading>
          </div>

        </div>
        <div class="w-full" v-else>
          <ul class="flex flex-col gap-5 w-full">

            <template v-for="wifi in listWifiOrdered">
              <li class="w-full cursor-pointer" @click="wifiName = wifi.ssid">
                <div :class="currentWifiName == wifi.ssid ? 'font-bold ' : ''"
                  class="w-full  border rounded  py-2 px-2 text-led-100 bg-led-400">
                  {{ wifi.ssid }}
                </div>


                <!-- <span>{{ wifi.ssid }} {{ wifi.rssi }}</span> -->

              </li>
            </template>
          </ul>

        </div>
      </div>

    </template>
  </Dialog>
</template>

<style scoped></style>
