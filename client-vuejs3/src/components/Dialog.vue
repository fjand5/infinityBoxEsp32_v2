<script setup>
const emit = defineEmits(["onClose"]);
const { show } = defineProps(['show'])
</script>

<template>
  <div class="w-screen">

    <div class="absolute w-[320px] max-w-xs z-10 right-[50%] top-0 bottom-0 translate-x-[50%] transition-all duration-300 pointer-events-none"
      :class="show ? 'pointer-events-auto opacity-100' : 'opacity-0'">
      <div class="absolute -z-10 w-full h-full bg-led-400 opacity-95"></div>
      <div class="w-full h-full p-2 flex flex-col gap-2">
        <div class="flex items-center justify-between bg-led-100 p-4 -m-2 text-led-400">
          <slot name="header" />
  
        </div>
        <div>

          <slot name="content" />
        </div>
      </div>
  
    </div>
  </div>
</template>

<style scoped></style>