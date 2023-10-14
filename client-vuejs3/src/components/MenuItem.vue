<script setup>
import { useSlots } from 'vue'
const emit = defineEmits(['itemClick'])
const slots = useSlots()

defineProps({
  label: String,
  detail: String
})

const itemClick=()=>{
  emit('itemClick')
}
</script>

<template>
  <div @click="itemClick" class="w-full h-16 bg-inherit flex items-center">
    <div v-if="slots.icon" class="basis-1/6 h-2/3 aspect-square flex items-center">
      <slot name="icon"></slot>
    </div>

    <div class="basis-5/6 flex flex-col justify-between">
      <span class="font-semibold">{{ label }}</span>
      <span class="font-light text-sm">{{ detail }}</span>
    </div>
  </div>
</template>

<style scoped></style>
