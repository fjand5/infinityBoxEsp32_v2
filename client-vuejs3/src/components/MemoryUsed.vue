<script setup>
import { reactive, ref, watch } from 'vue';
import { useLedStateStore } from '../store'
import { storeToRefs } from 'pinia';
const ledStateStore = useLedStateStore();
const { percent } = defineProps(['percent'])

</script>

<template>
  <div class="bg-led-200 h-6 relative ">
    <div class="bg-led-500 h-full transition-all duration-500" :style="{width: `${percent}%`}"></div>
    <span class="absolute top-0 text-led-100 drop-shadow-lg translate-x-[-100%] transition-all duration-500" :style="{left: `max(calc(${percent}%),50px)`}">
      {{ `${percent.toFixed(1)}%` }}
    </span>
  </div>
</template>

<style scoped></style>
