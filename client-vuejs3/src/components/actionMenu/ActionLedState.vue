<script setup>

import { useLedStateStore, useLedSelectedStore, useLiveTimeSelectedStore } from "../../store";
const emit = defineEmits(["onDone", "onInsertSampleSelect"]);

const { index } = defineProps(["index"]);

const ledStateStore = useLedStateStore();

const onDelete = ({ groupIndex, stateIndex }) => {
  // useLedSelectedStore().clearSelected()
  // useLiveTimeSelectedStore().clearSelected()
  emit("onDone")
  setTimeout(()=>{
    ledStateStore.deleteLedState({ groupIndex, stateIndex })

  },200)
}
const onInsertLedState = ({ groupIndex, stateIndex }) => {
  emit("onDone")

  setTimeout(()=>{
    ledStateStore.insertLedState({ groupIndex, stateIndex })

  },200)
}
const onInsertRepeater = ({ groupIndex, stateIndex }) => {
  emit("onDone")
  setTimeout(()=>{
    ledStateStore.insertRepeater({ groupIndex, stateIndex })

  },200)
}
const onInsertSampleSelect = (index) => {
  emit("onInsertSampleSelect")
}
const onDeleteInsideRepeater = ({ groupIndex, stateIndex }) => {
  emit("onDone")
  setTimeout(()=>{
    ledStateStore.deleteInsideRepeater({ groupIndex, stateIndex })

  },200)
}
</script>

<template>
  <ul class=" mt-10 text-led-100 w-full h-fit flex flex-col gap-5  items-center  justify-between">
    <li @click="() => onInsertSampleSelect(index)">
      Thêm Mẫu Có Sẵn

    </li>
    <li @click="() => onInsertLedState(index)">
      Thêm Trạng Thái
    </li>
    <li v-if="index.stateIndex >= 0 && !ledStateStore.checkIsRepeater({ groupIndex: index.groupIndex, stateIndex: index.stateIndex })"
      @click="() => onInsertRepeater(index)">
      Thêm Bộ Lặp
    </li>
    <li v-if="ledStateStore.checkIsRepeater({ groupIndex: index.groupIndex, stateIndex: index.stateIndex })" class="dangerous" @click="() => onDeleteInsideRepeater(index)">
      Xóa Cả Phần Trong Bộ lăp
    </li>
    <li v-if="index.stateIndex >= 0" class="dangerous" @click="() => onDelete(index)">
      Xóa
    </li>
  </ul>
</template>

<style scoped>
li {
  @apply border-b-[1px] border-led-100;
}

li.dangerous {
  @apply border-b-[1px] border-led-500 text-led-500;
}
</style>
