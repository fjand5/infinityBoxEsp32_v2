<script setup>
defineProps(['modelValue'])
const emit = defineEmits(['update:modelValue'])
const onClick = (e) => {
  emit('update:modelValue', e.target.checked)
}
</script>

<template>
  <div class="w-full h-fit flex flex-col gap-4 relative">
    <input :checked="modelValue" @click="onClick"
      class="appearance-none rounded-full w-20 h-10 bg-dark-200 relative before:content-[''] before:w-8 before:h-8 before:bg-dark-100 before:border-dark-400 before:border before:absolute before:rounded-full before:top-1 before:left-2 before:transition-all before:checked:bg-dark-400 before:checked:left-10"
      type="checkbox">
  </div>
</template>

<style scoped></style>
