<script setup>
import { onMounted, ref } from 'vue';
const timerId = ref(null)
const widthPercent = ref(null)
const widthPercentSig = ref(0.1)
onMounted(() => {
  // timerId.value = setInterval(() => {
  //   if (widthPercent.value > 66)
  //     widthPercentSig.value = -0.1
  //   if (widthPercent.value < 33)
  //     widthPercentSig.value = 0.1
  //   widthPercent.value += widthPercentSig.value;
  // }, 10)
})
</script>

<template>
  <div class="w-full h-[5px] bg-dark-200 relative overflow-hidden">
    <div class="h-1 bg-dark-300 running relative">

    </div>
  </div>
</template>

<style scoped>
.running {
  animation: running 3s ease-in-out infinite;
}

@keyframes running {
  0%,100%{
    width: 0%;
    left: 0;
  }
  50%{
    width: 100%;
    left: 100%;
  }

}
</style>
