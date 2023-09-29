<script setup>
import IconEye from './icon/IconEye.vue';
import IconEyeSlash from './icon/IconEyeSlash.vue';

import { useMetaStore } from "../store";


import Dialog from './Dialog.vue';
import { onMounted, ref, watch } from 'vue';
import { storeToRefs } from 'pinia';
import IconClose from './icon/IconClose.vue';
const metaStore = useMetaStore()
const { meta } = storeToRefs(metaStore)
const emit = defineEmits(["onClose"]);

const { show } = defineProps(['show'])


const password = ref('')
const showPassword = ref(false)
const showPassword2 = ref(false)
const password2 = ref('')
const passwordError = ref()
const wifiNameError = ref()

onMounted(() => {
  // wifiSetupStore.loadWifiSetup()
  // setInterval(() => {
  //   wifiSetupStore.alive()
  // }, 5000)

  // console.log('meta.value')
  // password.value = meta.value.wifi['ApPASS']
  // password2.value = meta.value.wifi['ApPASS']
})
// watch(meta.wifi, (n, o) => {
//   console.log(n)
//   password.value = meta.value.wifi['ApPASS']
//   password2.value = meta.value.wifi['ApPASS']
// })

const onClose = () => {
  emit('onClose')
}
const submitWifiInfo = () => {
  if (password.value !== password2.value) {
    return
  }
  if (password.value.length < 7) {
    passwordError.value = "Mật khẩu phải hơn 8 ký tự"
    return
  }
  if (password.value.length > 15) {
    passwordError.value = "Mật khẩu phải ít hơn 16 ký tự"
    return
  }
  passwordError.value = false


  if (meta.value.wifi['ApSSID'].length < 7) {
    wifiNameError.value = "Tên wifi phải hơn 8 ký tự"
    return
  }
  if (meta.value.wifi['ApSSID'].length > 15) {
    wifiNameError.value = "Tên wifi phải ít hơn 16 ký tự"
    return
  }
  if (!(/^[A-Z0-9 _]*[A-Z0-9][A-Z0-9 _]*$/i.test(meta.value.wifi['ApSSID'].length))) {
    wifiNameError.value = "Tên wifi không được chứa ký tự đặc biệt"
    return
  }
  wifiNameError.value = false

  meta.value.wifi['ApPASS'] = password.value

  metaStore.commitApSSID(meta.value.wifi['ApSSID'])
  metaStore.commitApPASS(meta.value.wifi['ApPASS'])
  emit('onClose')
}
</script>

<template>
  <Dialog :show="show">
    <template v-slot:header>
      <div class="flex w-full relative">

        <span class="absolute bottom-[50%] right-[50%] translate-x-[50%] translate-y-[50%]">
          Thông tin Wifi

        </span>
        <IconClose @click="() => onClose()" class="ml-auto" />
      </div>
    </template>

    <template v-slot:content>
      <div class="my-8">


        <div class="mb-4">
          <label class=" text-led-100 text-sm font-bold mb-2" for="wifiname">
            Tên wifi
            <span v-if="wifiNameError" class="flex text-led-500 font-normal">{{ wifiNameError }}</span>

          </label>
          <input
            class="appearance-none border border-led-100 rounded w-full py-2 px-3 text-led-100 outline-none bg-led-400"
            id="wifiname" type="text" v-model="meta.wifi['ApSSID']" placeholder="Tên wifi">
        </div>
        <div class="mb-4">
          <label class=" text-led-100 text-sm font-bold mb-2" for="password">
            Mật khẩu
          </label>
          <div class="flex items-center gap-2  border border-led-100 rounded w-full py-2 px-3">

            <input class="appearance-none text-led-100 outline-none bg-led-400 w-full" id="password"
              :type="showPassword ? 'text' : 'password'" v-model="password" placeholder="Mật khẩu">
            <div class="">

              <IconEyeSlash v-if="showPassword" @click="() => showPassword = false" />
              <IconEye v-else @click="() => showPassword = true" />
            </div>
          </div>
        </div>
        <div class="mb-4">
          <label class=" text-led-100 text-sm font-bold mb-2 flex gap-2" for="password2">
            Nhập lại mật khẩu
            <span v-if="passwordError" class="flex text-led-500 font-normal">{{ passwordError }}</span>

          </label>

          <div class="flex items-center gap-2  border border-led-100 rounded w-full py-2 px-3">
            <input @input="() => {
              if (password !== password2) {
                passwordError = 'Mật khẩu không khớp'
              } else {
                passwordError = false
              }
            }" class="appearance-none w-full text-led-100 outline-none bg-led-400" id="password2"
              :type="showPassword2 ? 'text' : 'password'" v-model="password2" placeholder="Nhập lại mật khẩu">

            <div class="">

              <IconEyeSlash v-if="showPassword2" @click="() => showPassword2 = false" />
              <IconEye v-else @click="() => showPassword2 = true" />
            </div>
          </div>

        </div>
        <div class="flex flex-col gap-3 items-center justify-between">
          <div class="flex flex-col gap-1 justify-start">

            <span class="inline-block align-baseline font-bold text-sm text-led-500 text-left">
              Vui lòng ghi nhớ mật khẩu sau khi đổi.
            </span>
            <span class="inline-block align-baseline font-bold text-sm text-led-500 text-left">
              Bạn không nên đổi mật khẩu nếu không thực sự cần thiết.
            </span>
          </div>
          <div class="flex justify-between w-full">

            <button @click="() => onClose()"
              class="border-[1px] border-led-100 text-led-100 font-bold py-2 px-4 rounded outline-none" type="button">
              Thoát
            </button>
            <button @click="() => submitWifiInfo()" class="bg-led-100 text-white font-bold py-2 px-4 rounded outline-none"
              type="button">
              Xác nhận
            </button>
          </div>

        </div>
      </div>

    </template>
  </Dialog>
</template>

<style scoped></style>
