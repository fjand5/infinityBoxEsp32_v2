<script setup>
import { onMounted, onUnmounted, ref } from "vue";
import { useEffectsStore } from "../store";
import { storeToRefs } from "pinia";
import Effect from "./Effect.vue"
import IconPlus from "./icon/IconPlus.vue";
import EffectAdjustment from "./EffectAdjustment.vue";
const effectsStore = useEffectsStore()
const { effects } = storeToRefs(effectsStore)
const adjustmentIndex = ref(undefined)
onMounted(() => {
  effectsStore.loadEffects()
})
const addEffect = (effect) => {
  effectsStore.add(effect)
}
const updateEffect = (effect, index) => {
  effectsStore.update({ effect, index })
}
</script>

<template>
  <div class="flex flex-col gap-2">
    <EffectAdjustment @onCreate="(effect) => {
      addEffect(effect)
      adjustmentIndex = undefined
    }" @onUpdate="({ effect, index }) => {
  updateEffect(effect, index)
  adjustmentIndex = undefined
}" @on-close="adjustmentIndex = undefined" v-if="adjustmentIndex != undefined" :index="adjustmentIndex" />

    <template v-for="(effect, index) in effects">
      <div>
        <Effect :index="index" :effect-name="effect.effectName" :alive-time="effect.aliveTime" :movement="effect.movement"
          :palette="effect.palette" :tick="effect.tick" @on-adjusment="(index) => adjustmentIndex = index" />
      </div>
    </template>
    <div @click="() => adjustmentIndex = -1"
      class="flex justify-center border-[1px] rounded-md p-2 gap-2 shadow-lg cursor-pointer  select-none">

      <IconPlus />
    </div>
  </div>
</template>

<style scoped></style>