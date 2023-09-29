<script setup>
// import { effectName2Text, movement2Text } from '../utlis';
import IconDown from './icon/IconDown.vue';
import IconTrash from './icon/IconTrash.vue';
import IconUp from './icon/IconUp.vue';

import { useEffectsStore } from "../store";
import IconAdjustment from './icon/IconAdjustment.vue';

const emit = defineEmits(["onAdjusment"]);
const { index, effectName, aliveTime, movement, palette, tick } = defineProps(['index', 'effectName', 'aliveTime', 'movement', 'palette', 'tick'])

const effectsStore = useEffectsStore()

const moveUp = ()=>{
  effectsStore.moveUp(index)
}
const moveDown = ()=>{
  effectsStore.moveDown(index)
}
const remove = ()=>{
  effectsStore.remove(index)
}
</script>

<template>
  <div class="border-[1px] rounded-md p-2 flex flex-col gap-2 shadow-lg">
    <div class="flex items-center font-medium text-md justify-between ">
      <span>
        {{ effectName2Text(effectName) }}
      </span>
      <div class="flex items-center gap-5">
        <IconAdjustment class="cursor-pointer  select-none" @click="$emit('onAdjusment',index)" />
        <IconTrash class="cursor-pointer  select-none" @click="remove" />
        <div>
          <IconUp class="cursor-pointer  select-none" @click="moveUp" />
          <IconDown class="cursor-pointer  select-none" @click="moveDown"/>
        </div>
      </div>
    </div>
    <div class="w-full h-[1px] bg-led-100"></div>

    <div class="flex font-normal text-sm justify-between">
      <span>
        Thời gian:
      </span>
      <span> {{ aliveTime / 1000 }} giây
      </span>
    </div>
    <div class="flex font-normal text-sm justify-between">
      <span>
        Hướng:
      </span>
      <span> {{ movement2Text(movement) }}
      </span>
    </div>
    <div class="flex font-normal text-sm justify-between">
      <span>
        Màu:
      </span>
      <div class="flex gap-2">
        <template v-for="color in palette">

          <div class="w-5 h-5 shadow-md" :style="{ 'background-color': color }"></div>

        </template>
      </div>
    </div>
    <div class="flex font-normal text-sm justify-between">
      <span>
        Tốc độ:
      </span>
      <span> {{ tick }} ms
      </span>
    </div>
  </div>
</template>

<style scoped></style>