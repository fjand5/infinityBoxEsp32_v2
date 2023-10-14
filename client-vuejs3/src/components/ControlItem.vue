<script setup>
import { useSlots } from 'vue'
const slots = useSlots()
</script>

<template>
  <div class="w-full h-16 bg-inherit flex items-center">
    <div v-if="slots.icon" class="basis-1/6 h-2/3 aspect-square flex items-center">
      <slot name="icon"></slot>
    </div>

    <div :class="slots.icon?'basis-5/6':'w-full'" class=" flex flex-col justify-between">
     <slot name="content"></slot>
    </div>
  </div>
</template>

<style scoped></style>
