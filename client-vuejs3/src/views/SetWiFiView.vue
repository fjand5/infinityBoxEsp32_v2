<script setup>
import { onMounted, ref } from 'vue';
import BaseView from '~/views/BaseView.vue';
import PasswordInput from '~/components/PasswordInput.vue'
import { WifiService } from '~/services';
import { useRouter } from 'vue-router';
import TextInput from '~/components/TextInput.vue';
const router = useRouter()
const wifiName = ref(null)
const wifiPassword = ref(null)
const isStation = ref(false)

const hasError = ref(false)
onMounted(async () => {
  wifiName.value = window.history.state.id;
  wifiPassword.value = window.history.state.pass;
  isStation.value = window.history.state.isStation;
})
const commit = async () => {
  try {
    if (isStation.value) {
      await WifiService.setApSSID(wifiName.value)
      await WifiService.setApPASS(wifiPassword.value)
    }else {
      await WifiService.setStaSSID(wifiName.value)
      await WifiService.setStaPASS(wifiPassword.value)
    }
    hasError.value = false

    router.back()
  } catch (error) {
    hasError.value = true
  }
}
</script>

<template>
  <div class="w-full h-full">
    <BaseView :label="wifiName || 'Nhập wifi thủ công'">
      <div class="w-full flex flex-col gap-10">
        <span v-if="hasError" class="text-red-400 text-sm font-light">Thất bại</span>
        <TextInput v-model="wifiName" label="Tên mạng"></TextInput>
        <PasswordInput v-model="wifiPassword"></PasswordInput>
        <div class="flex justify-end gap-10 text-dark-400">
          <button class="">HỦY</button>
          <button @click="commit" class="">LƯU</button>
        </div>
      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
