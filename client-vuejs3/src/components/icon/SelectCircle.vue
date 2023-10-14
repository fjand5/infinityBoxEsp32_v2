<script setup>
const props = defineProps(['selected'])

</script>

<template>
  <div :class="props.selected?'border-dark-400':'border-dark-500'" class="w-full h-full rounded-full  border-[2px] flex justify-center items-center">
    <div v-if="props.selected" class="w-2 h-2 rounded-full bg-dark-400"></div>
  </div>
</template>

<style scoped></style>
