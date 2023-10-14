<script setup>
</script>

<template>
  <div class="fixed top-0 bottom-0 left-0 right-0  z-40">
    <div class=" w-screen h-screen bg-dark-200 opacity-90">
    </div>
    <div class="absolute bottom-[50%] right-[50%] translate-x-[50%] translate-y-[50%] w-full   max-w-[calc(theme(spacing.72))] max-h-[calc(100vh-theme(spacing.10))] h-full">
      <slot></slot>
    </div>

  </div>
</template>

<style scoped></style>
