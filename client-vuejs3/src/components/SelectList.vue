<script setup>
import Modal from '~/components/base/Modal.vue';
import SelectCircle from '~/components/icon/SelectCircle.vue';
import Close from './icon/Close.vue';
const props = defineProps(['label', 'listItem', 'show', 'selectedItem'])
const emit = defineEmits(['update:selectedItem', 'update:show'])

const itemSelect = (item) => {
  emit('update:selectedItem', item)

}
const close = () => {
  emit('update:show', false)
}
</script>

<template>
  <Modal>
    <div class="w-full h-full bg-dark-200 rounded-3xl shadow-xl">
      <div class="w-full h-full flex flex-col">
        <div class="p-5 flex items-center">
          <span class="font-medium text-3xl">
            {{ label }}
          </span>
          <div @click="close" class="ml-auto h-full w-6">

            <Close></Close>
          </div>
        </div>
        <div class="w-full h-[1px] shrink-0 bg-dark-400"></div>
        <div class="w-full flex-1 overflow-auto p-4">
          <div class="w-full h-full  overflow-y-scroll appearance-none bg-inherit flex flex-col gap-4">
            <template v-for="item in listItem">
              <div @click="() => itemSelect(item)" class="flex gap-6 items-center w-full h-8">
                <div class="h-full aspect-square p-1">
                  <SelectCircle :selected="selectedItem == item"></SelectCircle>
                </div>
                <span class="font-normal text-lg">
                  {{ item }}
                </span>
              </div>
            </template>
          </div>
        </div>
      </div>
    </div>
  </Modal>
</template>

<style scoped></style>
