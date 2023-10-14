<script setup>
import { ref, watch } from 'vue';
defineProps(['modelValue','label'])
defineEmits(['update:modelValue'])
</script>

<template>
  <div class="w-full h-fit flex flex-col gap-4">
    <span class="text-dark-400 font-light">{{ label }}</span>
    <div class="flex flex-col gap-1">
      <input :value="modelValue" @input="$emit('update:modelValue', $event.target.value)"
        type="text" class="bg-inherit outline-none text-dark-500" />
      <div class="w-full h-[2px] bg-dark-400 opacity-60"></div>
    </div>
  </div>
</template>

<style scoped></style>
