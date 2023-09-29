<script setup>
import { onMounted, ref } from "vue";
import { useLedStateStore } from "../../store";
import {
  fadeInSample,
  fadeOutSample,
  fadeInAndOutSample,
  blinkSample,
  leftToRightSample,
  rightToLeftSample,
  leftRightSample,
  leftMeteorSample,
  rightMeteorSample,
  leftRightMeteorSample,
  alternateBlinkSample,
  alternateFadeSample,
  stackingToLeftSample,
  stackingToRightSample,
  stackingToLeftFadeSample,
  stackingToRightFadeSample,
  blinkOneByOneSample,
  fadeOneByOneSample,
  waveSample,
  waveFadeSample,
openMeteorSample,
closeMeteorSample
} from "../../utlis";
import { storeToRefs } from "pinia";
const emit = defineEmits(["onDone"]);
const numOfPort = ref(4)
const { index } = defineProps(["index"]);

const ledStateStore = useLedStateStore();
const { groups } = storeToRefs(ledStateStore)

const insertSample = (sample) => {
  emit('onDone')

  setTimeout(()=>{
    ledStateStore.insertSample({ ...index, sample })

  },200)
}
onMounted(()=>{
  numOfPort.value = groups.value[index.groupIndex].ports.length
})
</script>

<template>
  <ul class="flex text-led-100 gap-4 mt-5 flex-wrap">
    <li @click="() => insertSample(fadeInSample(numOfPort))">Sáng dần</li>
    <li @click="() => insertSample(fadeOutSample(numOfPort))">Tắt dần</li>
    <li @click="() => insertSample(fadeInAndOutSample(numOfPort))">Nhấp nháy dịu</li>
    <li @click="() => insertSample(blinkSample(numOfPort))">Nhấp nháy</li>
    <li @click="() => insertSample(leftToRightSample(numOfPort))">Trái qua phải</li>
    <li @click="() => insertSample(rightToLeftSample(numOfPort))">Phải qua trái</li>
    <li @click="() => insertSample(leftRightSample(numOfPort))">Lặp trái phải</li>
    <li @click="() => insertSample(leftMeteorSample(numOfPort))">Sao băng trái</li>
    <li @click="() => insertSample(rightMeteorSample(numOfPort))">Sao băng phải</li>
    <li @click="() => insertSample(leftRightMeteorSample(numOfPort))">Sao băng trái phải</li>
    <li @click="() => insertSample(alternateBlinkSample(numOfPort))">Nháy so le</li>
    <li @click="() => insertSample(alternateFadeSample(numOfPort))">Nháy so le dịu</li>
    <li @click="() => insertSample(stackingToLeftSample(numOfPort))">Dồn qua trái</li>
    <li @click="() => insertSample(stackingToRightSample(numOfPort))">Dồn qua phải</li>
    <li @click="() => insertSample(stackingToLeftFadeSample(numOfPort))">Dồn qua trái dịu</li>
    <li @click="() => insertSample(stackingToRightFadeSample(numOfPort))">Dồn qua phải dịu</li>
    <li @click="() => insertSample(blinkOneByOneSample(numOfPort))">Nháy từng cổng</li>
    <li @click="() => insertSample(fadeOneByOneSample(numOfPort))">Nháy từng cổng dịu</li>
    <li @click="() => insertSample(waveSample(numOfPort))">Lượn sóng</li>
    <li @click="() => insertSample(waveFadeSample(numOfPort))">Lượn sóng dịu</li>
    <li @click="() => insertSample(openMeteorSample(numOfPort))">Tỏa ra</li>
    <li @click="() => insertSample(closeMeteorSample(numOfPort))">Dồn vào</li>
  </ul>
</template>

<style scoped>
li {
  @apply text-led-100 border-[1px] border-led-100 p-1 rounded-sm;
}
</style>
