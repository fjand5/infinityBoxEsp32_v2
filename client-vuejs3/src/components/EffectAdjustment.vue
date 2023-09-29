<script setup>
import { onMounted, onUnmounted, reactive, ref, watch } from 'vue';
import Dialog from './Dialog.vue';
import IconClose from './icon/IconClose.vue';
// import { effectName2Text, movement2Text, efffectList, toggleMovement } from '../utlis';
import IconPlus from './icon/IconPlus.vue';
import IconMinus from './icon/IconMinus.vue';
import IconCheck from './icon/IconCheck.vue';
import { ColorPicker } from 'vue-color-kit'
import 'vue-color-kit/dist/vue-color-kit.css'
import { useEffectsStore } from '../store';
import { storeToRefs } from 'pinia';
const emit = defineEmits(["onClose", "onCreate", "onUpdate"]);

const { show, index } = defineProps(['show', 'index'])
const effectsStore = useEffectsStore()
const { effects } = storeToRefs(effectsStore)

const showColorPicker = ref(false)
const color = ref()
const colorPaleteIndex = ref()


const effect = reactive({
  effectName: 'Effect_Meteor',
  aliveTime: 15000,
  movement: 'Movement_Forward',
  palette: ['#ff0000', '#00ff00', '#0000ff', '#ffffff'],
  tick: 50,
  data: {
    length: 10,
    from: 25,
    to: 255
  }

});
onMounted(() => {
  if (index >= 0)
    Object.assign(effect, effects.value[index])
})

onUnmounted(() => {
  effectsStore.playAll()
})
const submit = (index) => {
  const effectObject = JSON.parse(JSON.stringify(effect))

  if (index === -1) {
    emit("onCreate", effectObject)
  } else {
    emit("onUpdate", { effect: effectObject, index })
  }
}
const preview = async (index) => {
  effectsStore.update({ effect: effect, index })
  await effectsStore.preview(index)
}
const changeColor = (c) => {
  effect.palette[colorPaleteIndex.value] = c.hex
}
const selectEffect = (e) => {
  effect.effectName = e
}


</script>

<template>
  <Dialog :show="true">
    <template v-slot:header>
      <div class="flex w-full relative">

        <span class="absolute bottom-[50%] right-[50%] translate-x-[50%] translate-y-[50%]">
          {{ index === -1 ? 'Tạo hiệu ứng' : 'Chỉnh sửa hiệu ứng' }}
        </span>
        <IconClose @click="() => $emit('onClose')" class="ml-auto cursor-pointer  select-none" />
      </div>
    </template>

    <template v-slot:content>
      <div class="p-2 flex-col flex gap-3 justify-between">

        <div class="flex flex-nowrap items-center py-5 font-medium text-md justify-between overflow-x-scroll gap-5">
          <template v-for="e in efffectList">
            <span @click="() => selectEffect(e)"
              :class="`${e === effect.effectName ? 'border-[1px]' : ''} select-none whitespace-nowrap  cursor-pointer rounded-full border-led-100 p-1`">
              {{ effectName2Text(e) }}
            </span>
          </template>

        </div>
        <div class="w-full h-[1px] bg-led-100"></div>

        <div class="flex justify-between">
          <span class="w-24 shrink-0">
            Thời gian:
          </span>

          <div class="w-16 flex gap-1">
            <input class="shrink w-8 text-right bg-inherit outline-none" type="number" @input="event => {
              if (Number(event.target.value) > 3600) event.target.value = 3600
              if (Number(event.target.value) < 3) event.target.value = 3
              effect.aliveTime = Number(event.target.value) * 1000

            }" :value="effect.aliveTime / 1000">
            <span class="w-fit">

              giây
            </span>
          </div>
          <div class="flex gap-5 select-none">

            <IconPlus class="cursor-pointer  select-none" @click="() => {
              if (effect.aliveTime > 3600000) return
              effect.aliveTime += 1000

            }" />
            <IconMinus class="cursor-pointer  select-none" @click="() => {

              if (effect.aliveTime < 3000) return
              effect.aliveTime -= 1000
            }" />
          </div>
        </div>

        <div v-if="effect.effectName != 'Effect_Blink'" class="flex justify-between">
          <span class="w-24 shrink-0">
            Độ dài:
          </span>

          <div class="w-16 flex gap-1">
            <input class="shrink w-8 text-right bg-inherit outline-none" type="number" @input="event => {
              if (Number(event.target.value) > 512) event.target.value = 512
              if (Number(event.target.value) < 3) event.target.value = 3
              effect.data.length = Number(event.target.value)

            }" :value="effect.data.length">
            <span class="w-fit">
              bóng
            </span>
          </div>
          <div class="flex gap-5 select-none">

            <IconPlus class="cursor-pointer  select-none" @click="() => {
              if (effect.data.count > 512) return
              effect.data.length += 1
            }" />
            <IconMinus class="cursor-pointer  select-none" @click="() => {
              if (effect.data.length <= 3) return
              effect.data.length -= 1
            }" />
          </div>
        </div>
        <div v-if="effect.effectName != 'Effect_Blink'" class="flex justify-between">
          <span class="w-24 shrink-0">
            Hướng:
          </span>
          <span @click="() => effect.movement = toggleMovement(effect.movement)" class="cursor-pointer select-none w-16">
            {{ movement2Text(effect.movement) }}
          </span>
        </div>
        <div v-if="effect.effectName != 'Effect_Rainbow'" class="flex justify-between">
          <span class="w-24 shrink-0">
            Màu:
          </span>
          <div class="flex gap-5">
            <template v-for="(paletteColor, index) in effect.palette">

              <div @click="() => {

                showColorPicker = true
                color = paletteColor
                colorPaleteIndex = index
              }" class="w-6 h-6 shadow-md cursor-pointer  select-none" :style="{ 'background-color': paletteColor }">
              </div>

            </template>
          </div>



          <div class="absolute" v-if="showColorPicker">
            <ColorPicker theme="light" :color="color" :colors-default="[]" @changeColor="changeColor" />
            <div class="w-full h-10 flex justify-end">
              <IconCheck class="cursor-pointer  select-none" @click="() => {
                showColorPicker = false
                colorPaleteIndex = undefined
              }" />
            </div>

          </div>
        </div>
        <div class="flex justify-between">
          <span class="w-24 shrink-0">
            Tốc độ:
          </span>

          <div class="w-16 flex gap-1">
            <input class="shrink w-8 text-right bg-inherit outline-none" type="number" @input="event => {
              if (Number(event.target.value) > 10000) event.target.value = 10000
              if (Number(event.target.value) < 10) event.target.value = 10
              effect.tick = Number(event.target.value)
            }" :value="effect.tick">
            <span class="w-fit">
              ms
            </span>
          </div>
          <div class="flex gap-5 ">
            <IconPlus class="cursor-pointer select-none" @click="() => {
              if (effect.tick > 10000) return
              effect.tick += 10
            }" />
            <IconMinus class="cursor-pointer select-none" @click="() => {
              if (effect.tick <= 10) return

              effect.tick -= 10
            }" />
          </div>
        </div>
        <div v-if="effect.effectName === 'Effect_Blink'" class="flex justify-between">
          <span class="w-24 shrink-0">
            Tối thiểu:
          </span>
          <span class="w-16"> {{ effect.data.from }}
          </span>

          <div class="flex gap-5 ">
            <IconPlus class="cursor-pointer  select-none" @click="() => {
              if (effect.data.from >= effect.data.to) return
              if (effect.data.from >= 255) return
              effect.data.from += 10

            }" />
            <IconMinus class="cursor-pointer  select-none" @click="() => {
              if (effect.data.from >= effect.data.to) return
              if (effect.data.from >= 255) return
              effect.data.from -= 10
            }" />
          </div>
        </div>
        <div v-if="effect.effectName === 'Effect_Blink'" class="flex justify-between">
          <span class="w-24 shrink-0">
            Tối đa:
          </span>
          <span class="w-16"> {{ effect.data.to }}
          </span>

          <div class="flex gap-5 ">
            <IconPlus class="cursor-pointer  select-none" @click="() => {
              if (effect.data.from >= effect.data.to) return
              if (effect.data.from <= 0) return
              effect.data.to += 10
            }" />
            <IconMinus class="cursor-pointer  select-none" @click="() => {
              if (effect.data.from >= effect.data.to) return
              if (effect.data.from <= 0) return
              effect.data.to -= 10
            }" />
          </div>
        </div>
      </div>
      <div class="flex gap-5 w-full justify-between">

        <div v-if="index !== -1" @click="() => preview(index)"
          class="flex justify-center  w-full border-[1px] border-led-100 rounded-md p-2 gap-2 shadow-lg cursor-pointer  select-none">
          Xem trước
        </div>
        <div @click="() => submit(index)"
          class="flex justify-center w-full border-[1px] border-led-100 rounded-md p-2 gap-2 shadow-lg cursor-pointer  select-none">
          OK
        </div>
      </div>
    </template>
  </Dialog>
</template>

<style scoped></style>