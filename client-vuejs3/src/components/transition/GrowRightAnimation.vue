<script setup>
</script>

<template>
  <Transition name="grow">
    <slot />
  </Transition>
</template>

<style scoped>
.grow-enter-active{
  transition: all 0.8s cubic-bezier(1, 0.5, 0.8, 1);
  

}
.grow-leave-active {
  transition: all 0.2s cubic-bezier(1, 0.5, 0.8, 1);

}

.grow-enter-from,
.grow-leave-to {
  
  transform: translateX(-100%);
  opacity: 0;
}
</style>
