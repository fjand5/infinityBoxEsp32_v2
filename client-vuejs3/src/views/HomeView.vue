<script setup>
import Wifi from '~/components/icon/Wifi.vue';
import MenuItem from '~/components/menuItem.vue';
import { RouterLink } from 'vue-router'
import Search from '../components/icon/Search.vue';
import Microphone from '../components/icon/Microphone.vue';
import { onMounted, ref } from 'vue';
import System from '~/components/icon/System.vue';
import { SystemService } from '~/services';
import Stop from '~/components/icon/Stop.vue';
import Play from '~/components/icon/Play.vue';
import Next from '~/components/icon/Next.vue';
import Back from '~/components/icon/Back.vue';
import Power from '~/components/icon/Power.vue';


const controlBarRef = ref(null)
const systemData = ref()
const isStop = ref(false)
const isPowerOn = ref(true)

onMounted(async () => {
  systemData.value = await SystemService.getSystem()
  isStop.value = systemData.value['stop']
  isPowerOn.value = systemData.value['powerOn']
  // system.autoMode = result['autoMode']
  // system.onMicrophone = result['onMicrophone']
  // system.brightness = result['brightness']
  // system.effectName = result['effectName']
  // system.palette = result['palette']


})

const homeScroll = (e) => {
  const target = e.target
  if (target.scrollTop > 96) {
    controlBarRef.value.style.top = (target.scrollTop - 96) + 'px'
  }
  else if (target.scrollTop == 0) {
    // trường hợp cuộn nhanh quá, không qua mốc 96 sẽ gặp lỗi
    controlBarRef.value.style.top = 0
  }
}
const toggleStop = async () => {
  const res = await SystemService.setStop(!isStop.value)
  isStop.value = res['newValue']
  systemData.value['stop'] = isStop.value
}
const togglePower = async () => {
  const res = await SystemService.setPowerOn(!isPowerOn.value)
  isPowerOn.value = res['newValue']
  systemData.value['powerOn'] = isPowerOn.value
}
const nextEffect = async () => {
  await SystemService.setNextEffect()
  isStop.value = false
  systemData.value['stop'] = isStop.value
}
const previousEffect = async () => {
  await SystemService.setPreviousEffect()
  isStop.value = false


}
</script>

<template>
  <div @scroll="homeScroll" class=" w-full h-full flex flex-col relative overflow-y-scroll">
    <div class="relative bg-dark-100 flex flex-col gap-6 mb-8 z-10">
      <div class=" flex justify-between items-center">

        <span class="font-semibold text-4xl">
          Cài đặt
        </span>
        <div @click="togglePower" class="h-8 aspect-square transition-all"
        :class="isPowerOn?'stroke-dark-300 drop-shadow-[0_0px_5px_theme(colors.dark.300)]':'stroke-dark-500/60'"
        >
          <Power></Power>
        </div>
      </div>
      <div ref="controlBarRef" class="relative py-4 bg-inherit">
        <div
          class="border border-dark-400 w-full h-14 rounded-full bg-dark-200 flex  justify-center gap-10 items-center px-3 ">
          <div @click="previousEffect" class=" aspect-square h-10 relative">
            <Back></Back>
          </div>
          <div @click="toggleStop" class="aspect-square h-10 relative">
            <Transition name="bounce">
              <Stop class="absolute" v-if="isStop"></Stop>
              <Play class="absolute" v-else></Play>
            </Transition>
          </div>
          <div @click="nextEffect" class="aspect-square h-10 relative">
            <Next></Next>
          </div>
        </div>
      </div>
    </div>
    <div class="relative w-full ">
      <RouterLink to="/wifi">
        <MenuItem label="Mạng và Internet" detail="Kết nối Wi-Fi, điểm phát sóng">
        <template #icon>
          <div class="h-8 aspect-square">
            <Wifi />
          </div>
        </template>
        </MenuItem>
      </RouterLink>
      <RouterLink to="/microphone">
        <MenuItem label="Microphone" detail="Độ nhạy, beat của microphone">
        <template #icon>
          <div class="h-8 aspect-square">
            <Microphone />
          </div>
        </template>
        </MenuItem>
      </RouterLink>
      <RouterLink :to="{
        name: 'system'
        , force: true,
        state: { params: { systemData: JSON.stringify(systemData) } }
      }">
        <MenuItem label="Hệ thống" detail="Độ sáng, tự động chuyển hiệu ứng">
        <template #icon>
          <div class="h-8 aspect-square">
            <System />
          </div>
        </template>
        </MenuItem>
      </RouterLink>
    </div>
  </div>
</template>

<style scoped></style>
