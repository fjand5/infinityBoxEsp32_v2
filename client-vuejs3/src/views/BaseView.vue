<script setup>
import { useRouter } from 'vue-router'
import Left from '../components/icon/Left.vue';
import { ref } from 'vue';
const router = useRouter()
defineProps({
  label: String
})
const navBarRef = ref(null)
const hideLabel = ref(null)

const itemsScroll = (e) => {
  const target = e.target
  hideLabel.value = target.scrollTop > 60
}
function prevRoutePath() {
  router.back()
}

</script>

<template>
  <div class="w-full h-full relative">
    <div ref="navBarRef"
      class="fixed z-20 top-0 w-screen max-w-sm -mx-4 h-14 py-10 px-4 flex gap-5 justify-between items-center"
      :class="hideLabel ? 'bg-dark-200' : ' bg-dark-100'">
      <div @click="prevRoutePath" class="h-8 aspect-square">
        <Left />
      </div>
      <span class="font-medium text-lg  transition-all duration-500" :class="hideLabel ? 'opacity-100' : 'opacity-0'">
        {{ label }}
      </span>
      <slot name="rightIcon"></slot>
    </div>
    <div @scroll="itemsScroll" class="w-full h-full overflow-y-scroll">
      <div class="relative bg-dark-100 flex flex-col gap-6 mb-8 z-10 mt-12 transition-all duration-500"
        :class="!hideLabel ? 'opacity-100' : 'opacity-0'">
        <span class="font-semibold text-4xl">{{ label }}</span>
      </div>
      <slot></slot>
    </div>
  </div>
</template>

<style scoped></style>
