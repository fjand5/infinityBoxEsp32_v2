<script setup>
import { useEffectsStore } from "../store";
const effectsStore = useEffectsStore()


const submit = async () => {
  await effectsStore.submitEffects()
}
</script>

<template>
    <div class="fixed w-full top-0 h-fit pointer-events-none ">
      <div class="relative top-[10px] right-2 max-w-xs w-full pointer-events-none">

        <div class="shadow-lg flex bg-led-500 rounded-full w-8 h-8 ml-auto border-[1px] border-led-400 pointer-events-auto">
          <button @click="submit" class="mx-auto my-auto text-white pointer-events-auto  select-none">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor"
              class="w-6 h-6">
              <path stroke-linecap="round" stroke-linejoin="round"
                d="M6 12L3.269 3.126A59.768 59.768 0 0121.485 12 59.77 59.77 0 013.27 20.876L5.999 12zm0 0h7.5" />
            </svg>
          </button>
        </div>
      </div>
    </div>
</template>

<style scoped></style>
