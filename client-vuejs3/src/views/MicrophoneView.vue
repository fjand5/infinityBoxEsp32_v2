<script setup>
import { onMounted, reactive, watch } from 'vue';
import ControlItem from '~/components/ControlItem.vue';
import Slider from '~/components/Slider.vue';
import Signal from '~/components/icon/Signal.vue';
import Bolt from '~/components/icon/Bolt.vue';
import BaseView from '~/views/BaseView.vue';
import { MicrophoneService } from '~/services'

const microphone = reactive({
  gain: 0,
  beat: 0,

})

onMounted(async () => {
  const result = await MicrophoneService.getMicrophone()
  microphone.gain = result['gain']
  microphone.beat = result['beat']
})


watch(() => microphone.gain, async (n, o) => {
  await MicrophoneService.setMicrophoneGain(n)
})
watch(() => microphone.beat, async (n, o) => {
  await MicrophoneService.setMicrophoneBeat(n)
})
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Microphone">
      <div class="flex flex-col gap-5">

        <ControlItem>
          <template #icon>
            <div class="h-8 aspect-square">
              <Signal />
            </div>
          </template>
          <template #content>
            <div>
              <Slider v-model="microphone.gain" :label="`Điều chỉnh độ nhạy: ${microphone.gain}`" :min="0" :max="100"
                :step="1"></Slider>
            </div>
          </template>
        </ControlItem>
        <ControlItem>
          <template #icon>
            <div class="h-8 aspect-square">
              <Bolt />
            </div>
          </template>
          <template #content>
            <div>
              <Slider v-model="microphone.beat" :label="`Điều chỉnh beat: ${microphone.beat}`" :min="0" :max="100"
                :step="1"></Slider>
            </div>
          </template>
        </ControlItem>

      </div>
    </BaseView>
  </div>
</template>

<style scoped>
</style>
