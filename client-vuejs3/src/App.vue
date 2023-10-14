<script setup>
import { RouterLink, RouterView } from 'vue-router'

</script>

<template>
  <div class="w-screen h-screen bg-dark-200">
    <div class="h-screen max-h-screen overflow-y-scroll bg-dark-100 max-w-sm mx-auto flex flex-col shadow-lg">
      <RouterView v-slot="{ Component, route }" >
        <Transition name="slide-fade">
          <component class="absolute max-w-sm pt-8 px-4" :is="Component" :key="route.path"/>
        </Transition>
      </RouterView>
    </div>
  </div>
</template>

<style scoped>
.slide-fade-enter-active {
  transition: all 0.4s ease-out;
}
.slide-fade-leave-active {
  transition: all 0.6s cubic-bezier(1, 0.5, 0.8, 1);
}
.slide-fade-enter-from,
.slide-fade-leave-to {
  transform: translateX(100%);
  opacity: 0;
}
</style>
