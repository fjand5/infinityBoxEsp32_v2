<script setup>
import { ref, watch } from 'vue';
defineProps(['modelValue'])
defineEmits(['update:modelValue'])

const showPassword = ref(false)
const toggleShowPassword = () => {
  showPassword.value = !showPassword.value
}
</script>

<template>
  <div class="w-full h-fit flex flex-col gap-4">
    <span class="text-dark-400 font-light">Mật khẩu</span>
    <div class="flex flex-col gap-1">
      <input :value="modelValue" @input="$emit('update:modelValue', $event.target.value)"
        :type="showPassword ? 'text' : 'password'" class="bg-inherit outline-none text-dark-500" />
      <div class="w-full h-[2px] bg-dark-400 opacity-60"></div>
    </div>
    <div class="flex gap-5 items-center">
      <input @change="toggleShowPassword" type="checkbox" :checked="showPassword"
        class="after:content[''] relative h-5 w-5 cursor-pointer appearance-none rounded-sm border border-dark-500 after:translate-x-[6px] after:translate-y-[6px] after:block after:w-[6px] after:h-[6px] after:rounded-[1px]  after:checked:bg-dark-400" />
      <span @click="toggleShowPassword"> Hiện mật khẩu</span>
    </div>
  </div>
</template>

<style scoped></style>
