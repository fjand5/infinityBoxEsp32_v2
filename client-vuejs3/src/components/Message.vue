<script setup>
import { storeToRefs } from 'pinia';
import { useMessageStore } from '../store'
import { onMounted, onUpdated, ref, watch } from 'vue';

const messageStore = useMessageStore()
const { message } = storeToRefs(messageStore)
const processBarWidth = ref(100)
const wrapp = ref(null);
const timer = ref(undefined)
const timerInterval = ref(undefined)
watch(message, (n) => {
  if (!n)
    return
  let time = n.time
  timer.value = setTimeout(() => {
    messageStore.clearMessage()
  }, time * 1000)
  const offsetWidth = wrapp.value.offsetWidth
  processBarWidth.value = offsetWidth
  let divValue = offsetWidth/250
  timerInterval.value = setInterval(()=>{
    processBarWidth.value = processBarWidth.value - divValue
    if(processBarWidth.value <= 0 ){
      clearInterval(timerInterval.value)
    }
  }, time*4)
})
const stopNow = () => {
  message.value = undefined
  processBarWidth.value = 0
  clearTimeout(timer.value)
}
</script>

<template>
  <div v-if="message" @click="() => {
    stopNow()
  }" class="fixed z-20 top-0 bottom-0 left-0 right-0 bg-led-400 opacity-60  select-none"></div>

  <div
  ref="wrapp"
    :class="[message ? 'h-16' : 'h-0', message && message.type == 'ERROR' ? 'bg-led-400 text-led-500' : 'bg-led-100 text-led-200']"
    class="fixed  transition-all duration-500 z-20 top-0 w-[320px]  flex justify-center items-center shadow-lg">
    {{ message?.text && message.text }}
    <div class="absolute left-0 z-20 bottom-0  h-1 "
      :class="message && message.type == 'ERROR' ? 'bg-led-500 ' : 'bg-led-200 '"
      :style="{
        width: `${processBarWidth}px`
      }"
      
      >
    </div>
  </div>
</template>

<style scoped>
</style>
