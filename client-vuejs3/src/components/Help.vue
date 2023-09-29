<script setup>
import IconClose from './icon/IconClose.vue';

const emit = defineEmits(["onClose"]);
const { show } = defineProps(['show'])
const onClose = () => {
  emit('onClose')
}
</script>

<template>
  <div class="absolute z-10 left-0 top-0 bottom-0 right-0 transition-all duration-300 pointer-events-none"
    :class="show ? 'pointer-events-auto opacity-100' : 'opacity-0'">
    <div class="absolute -z-10 w-full h-full bg-led-400 opacity-95"></div>
    <div class="p-2 flex flex-col">

      <IconClose @click="onClose" class="ml-auto  select-none" />
      <h2 class="text-center text-led-100 mb-5 text-2xl capitalize font-semibold"> Hướng Dẫn</h2>
      <ul class="text-led-100 flex flex-col gap-3">
        <li>
          1. Bấm vào nút mũi tên đỏ phía trên, bên phải để nạp chương trình vào mạch.
        </li>
        <li>
          2. Bấm vào các số thứ tự của từng hàng để thao tác: thêm, sửa, xóa.
        </li>
        <li>
          3. Bấm vào từng bóng led (xanh lá, trắng) để điều chỉnh độ sáng.
        </li>
        <li>
          4. Bấm vào số tốc độ ở từng hàng để chỉnh tốc độ chạy (càng lớn càng chậm).
        </li>
        <li>
          5. Chạy dịu nghĩa là chuyển trạng thái từ từ tạo cảm giác dịu nhẹ.
        </li>
      </ul>
    </div>

  </div>
</template>

<style scoped></style>