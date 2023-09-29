<script setup>
import { onMounted, ref, watch } from 'vue';
import Message from './components/Message.vue';
import Background from './components/Background.vue';
import Border from './components/Border.vue';
import Display from './components/Display.vue';
import Calendar from './components/Calendar.vue';
import NavBar from './components/NavBar.vue';
import { useMetaStore, useDisplayStore } from './store';
import { DateTimeApi } from './api';
import TextScreen from './components/TextScreen.vue';

const metaStore = useMetaStore();
const displayStore = useDisplayStore();

const screenType = ref();
onMounted(async () => {
  await metaStore.loadMetaData()
  await displayStore.loadDisplayData()
  const timestamp = Date.now();
  DateTimeApi.setDateTime(timestamp / 1000)
})

watch(metaStore, async (n, o) => {
  screenType.value = metaStore.meta.content.screen
})
</script>

<template>
  <div class="min-h-screen max-h-screen overflow-y-scroll bg-led-400 max-w-xs mx-auto flex flex-col shadow-lg">
    <div class=" w-full max-h-[100%]">
      <Message />
      <NavBar />
    </div>
    <div class="px-2 py-2 w-full h-full">
      <tabs class="w-full h-full">

        <tab v-if="screenType === 'Screen_Calendar'" name="Lịch">
          <Calendar></Calendar>
        </tab>
        <tab v-if="screenType === 'Screen_Text'" name="Chữ">
          <TextScreen></TextScreen>
        </tab>
        <tab name="Nền">
          <Background></Background>
        </tab>
        <tab name="Viền" class="w-full h-full">
          <Border></Border>
        </tab>
        <tab name="Màn Hình">
          <Display></Display>
        </tab>
      </tabs>
      <!-- <Suspense>
        <EffectList />
        <template #fallback>
          <div class="absolute top-[50%] left-[50%] translate-x-[-50%] translate-y-[-50%]">
            <IconLoading />
          </div>
        </template>
      </Suspense> -->
    </div>
    <!-- <Controller /> -->
    <SubmitButton />
  </div>
</template>

<style scoped></style>
