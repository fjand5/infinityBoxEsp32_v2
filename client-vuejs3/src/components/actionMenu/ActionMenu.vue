<script setup>
import IconClose from '../icon/IconClose.vue';
import IconLeft from '../icon/IconLeft.vue';

import ActionLedState from "../actionMenu/ActionLedState.vue";
import { ref } from "vue";
import ActionSampleMenu from './ActionSampleMenu.vue';
import FadeAnimation from '../transition/FadeAnimation.vue';
import Dialog from '../Dialog.vue';
const emit = defineEmits(["onClose"]);

const { index, show } = defineProps(['index', 'show'])
const showSampleMenu = ref(false)
const onClose = () => {
  emit('onClose')
}
</script>

<template>
  <Dialog :show="show">
    <template v-slot:header>
      <FadeAnimation>
        <IconLeft @click="() => showSampleMenu = false" v-if="showSampleMenu" />
      </FadeAnimation>
      <span v-if="showSampleMenu">
        Chọn mẫu có sẵn
      </span>
      <IconClose @click="onClose" :class="showSampleMenu ? '' : 'ml-auto'" />
    </template>
    <template v-slot:content>
      <ActionSampleMenu v-if="showSampleMenu" @onDone="() => { showSampleMenu = false; onClose() }" :index="index" />
      <ActionLedState v-else @onDone="onClose" @onInsertSampleSelect="() => showSampleMenu = true" :index="index" />
    </template>
  </Dialog>
</template>

<style scoped></style>