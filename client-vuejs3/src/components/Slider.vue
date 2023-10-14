<script setup>
import { onMounted, ref, watch } from 'vue';
const props = defineProps(['modelValue', 'label', 'min', 'max', 'step'])
defineEmits(['update:modelValue'])
const sliderInput = ref(null)
const widthMaskCss = ref('')
onMounted(() => {
  sliderInput.value.addEventListener('input', (e)=>updateMask(e.target.value))
  updateMask(props.modelValue)
})
const updateMask = (value) => {
  const range = sliderInput.value
  const ratio = (value - range.min) / (range.max - range.min)
  widthMaskCss.value = ratio * 100
}
watch(() => props.modelValue, (n) => {
  updateMask(n)
})
</script>

<template>
  <div class="w-full h-fit flex flex-col gap-4 relative">
    <span class="text-dark-500 font-light">{{ label }}</span>
    <input ref="sliderInput" :value="modelValue" @input="$emit('update:modelValue', $event.target.value)" :min="min"
      :max="max" :step="step" type="range" class="slider  outline-none h-[2px] w-full bg-dark-200 appearance-none" />
    <div :style="{
      width: widthMaskCss + '%'
    }" class="bg-dark-300 absolute bottom-0 left-0 h-[2px] w-full pointer-events-none"></div>
  </div>
</template>

<style scoped>
.slider::-webkit-slider-thumb {
  appearance: none;
  width: theme('spacing.6');
  height: theme('spacing.6');
  border-radius: 9999px;
  background: theme('colors.dark.400');
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: theme('spacing.6');
  height: theme('spacing.6');
  border-radius: 9999px;

  background: theme('colors.dark.400');
}
</style>
