<script setup>
import { onMounted, reactive, ref, watch } from 'vue';
import ControlItem from '~/components/ControlItem.vue';
import Slider from '~/components/Slider.vue';
import Toggle from '~/components/Toggle.vue';
import SelectList from '~/components/SelectList.vue';
import Light from '~/components/icon/Light.vue';
import { SystemService } from '~/services';
import BaseView from '~/views/BaseView.vue';
import { StringData } from '~/utlis';
import Time from '~/components/icon/Time.vue';
const selectedEffect = ref()
const selectedPalette = ref()
const showSelectEffect = ref(false)
const showSelectPalette = ref(false)
const system = reactive({
  autoMode: undefined,
  onMicrophone: undefined,
  brightness: undefined,
  effectName: undefined,
  palette: undefined,
  timeAutoChangeMode: undefined,

})
onMounted(async () => {
  let result
  try {
    result = JSON.parse(window.history.state.params.systemData);
  } catch (error) {
    result = await SystemService.getSystem()
  }
  system.autoMode = result['autoMode']
  system.onMicrophone = result['onMicrophone']
  system.brightness = result['brightness']
  system.effectName = result['effectName']
  system.palette = result['palette']
  system.timeAutoChangeMode = result['timeAutoChangeMode'] / 1000

  selectedEffect.value = StringData.effectNameToString(system.effectName)
  selectedPalette.value = StringData.paletteNameToString(system.palette)

})

watch(() => system.brightness, async (n, o) => {
  if (o === undefined) return
  await SystemService.setBrightness(n)
})
watch(() => system.autoMode, async (n, o) => {
  if (o === undefined) return
  await SystemService.setAutoMode(n)
})
watch(() => system.onMicrophone, async (n, o) => {
  if (o === undefined) return
  await SystemService.setOnMicrophone(n)
})
watch(() => system.effectName, async (n, o) => {
  if (o === undefined) return
  selectedEffect.value = StringData.effectNameToString(n)
})
watch(() => system.palette, async (n, o) => {
  if (o === undefined) return
  selectedPalette.value = StringData.paletteNameToString(n)
})
watch(() => system.timeAutoChangeMode, async (n, o) => {
  if (o === undefined) return
  await SystemService.setTimeAutoChangeMode(n * 1000)

})
watch(selectedEffect, async (n, o) => {
  if (o === undefined) return
  await SystemService.setEffectName(StringData.stringToEffectName(n))
})
watch(selectedPalette, async (n, o) => {
  if (o === undefined) return
  await SystemService.setEffectPalette(StringData.stringToPaletteName(n))
})
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Hệ thống">
      <div class="flex flex-col gap-5">

        <ControlItem>
          <template #icon>
            <div class="h-8 aspect-square">
              <Light />
            </div>
          </template>
          <template #content>
            <div>
              <Slider v-model="system.brightness" :label="`Điều chỉnh độ sáng: ${system.brightness}`" :min="0" :max="255"
                :step="5"></Slider>
            </div>
          </template>
        </ControlItem>

        <ControlItem>
          <template #content>
            <div class="flex justify-between items-center w-full">

              <div class="flex flex-col justify-between ">
                <span class="font-normal">Bật/tắt microphone</span>
                <span class="font-light text-sm">
                  {{ system.onMicrophone ? 'Đang bật microphone' : 'Đang tắt microphone' }}
                </span>
              </div>
              <div>
                <Toggle v-model="system.onMicrophone"></Toggle>
              </div>
            </div>
          </template>
        </ControlItem>
        <ControlItem>
          <template #content>
            <div class="flex justify-between items-center w-full">
              <div class="flex flex-col justify-between ">
                <span class="font-normal">Tự động chuyển hiệu ứng</span>
                <span class="font-light text-sm">
                  {{ system.autoMode ? 'Đang tự động chuyển hiệu ứng' : 'Không tự chuyển hiệu ứng' }}
                </span>
              </div>
              <div>
                <Toggle v-model="system.autoMode"></Toggle>
              </div>
            </div>
          </template>
        </ControlItem>

        <ControlItem v-if="system.autoMode != false">
          <template #icon>
            <div class="h-8 aspect-square">
              <Time></Time>
            </div>
          </template>
          <template #content>
            <div>
              <Slider v-model="system.timeAutoChangeMode"
                :label="`Thời gian chuyển hiệu ứng: ${system.timeAutoChangeMode}s`" :min="5" :max="60" :step="1"></Slider>
            </div>
          </template>
        </ControlItem>

        <ControlItem v-if="system.autoMode == false">
          <template #content>
            <div @click="() => showSelectEffect = true" class="flex justify-between items-center w-full">
              <div class="flex flex-col justify-between ">
                <span class="font-normal">Chọn hiệu ứng</span>
                <span class="font-light text-sm">
                  Bấm vào để chọn hiệu ứng từ danh sách
                </span>
              </div>
            </div>
          </template>
        </ControlItem>

        <ControlItem v-if="system.autoMode == false">
          <template #content>
            <div @click="() => showSelectPalette = true" class="flex justify-between items-center w-full">
              <div class="flex flex-col justify-between ">
                <span class="font-normal">Chọn màu</span>
                <span class="font-light text-sm">
                  Bấm vào để chọn màu từ danh sách
                </span>
              </div>
            </div>
          </template>
        </ControlItem>

        <Transition name="bounce">

          <SelectList v-if="showSelectEffect" v-model:show="showSelectEffect" v-model:selected-item="selectedEffect"
            label="Chọn hiệu ứng"
            :list-item='StringData.listEffectName.map((effect) => StringData.effectNameToString(effect))'>
          </SelectList>

        </Transition>
        <Transition name="bounce">

          <SelectList v-if="showSelectPalette" v-model:show="showSelectPalette" v-model:selected-item="selectedPalette"
            label="Chọn màu"
            :list-item='StringData.listPaletteName.map((palette) => StringData.paletteNameToString(palette))'>
          </SelectList>
        </Transition>

      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
