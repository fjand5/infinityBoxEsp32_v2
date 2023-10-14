<script setup>
import { RouterLink } from 'vue-router'
import { onMounted, ref } from 'vue';
import { WifiService } from '~/services';
import BaseView from '~/views/BaseView.vue';
import LoadingLine from '~/components/LoadingLine.vue';
import Wifi from '~/components/icon/Wifi.vue';
import Plus from '~/components/icon/Plus.vue';
import Refesh from '~/components/icon/Refesh.vue';
import { wifiUtlis } from '~/utlis'
import MenuItem from '~/components/menuItem.vue';
import Signal from '~/components/icon/Signal.vue';
const nearWifi = ref([])
const currentWifi = ref(null)
onMounted(async () => {
  currentWifi.value = await WifiService.getWifi()
  nearWifi.value = await WifiService.nearWifi()
  nearWifi.value = nearWifi.value.filter((wifi) => {
    return wifi.ssid != currentWifi.value.StaSSID
  })
})
const refesh = async () => {
  nearWifi.value = []
  nearWifi.value = await WifiService.nearWifi()
  nearWifi.value = nearWifi.value.filter((wifi) => {
    return wifi.ssid != currentWifi.value.StaSSID
  })
}
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Thiết lập Wifi">
      <template #rightIcon>
        <div @click="refesh" v-if="nearWifi.length" class="h-8 aspect-square">
          <Refesh />
        </div>
      </template>
      <RouterLink :to="{
        name: 'setWifi'
        , force: true,
        state: {
          isStation: true,
          id: currentWifi?.ApSSID ? currentWifi.ApSSID : '',
          pass: currentWifi?.ApPASS ? currentWifi.ApPASS : ''
        }
      }">
        <MenuItem :label="currentWifi?.ApSSID ? currentWifi.ApSSID : ''" detail="Tên wifi và mật khẩu của Spex phát ra">
        <template #icon>
          <div class="h-8 aspect-square">
            <Signal />
          </div>
        </template>
        </MenuItem>
      </RouterLink>
      <RouterLink :to="{
        name: 'setWifi'
        , force: true,
        state: {
          id: currentWifi?.StaSSID ? currentWifi.StaSSID : '',
          pass: currentWifi?.StaPASS ? currentWifi.StaPASS : ''
        }
      }">
        <MenuItem :label="currentWifi?.StaSSID ? currentWifi.StaSSID : ''"
          :detail="'Đã kết nối, ip: ' + currentWifi?.ip || ''">
        <template #icon>
          <div class="h-8 aspect-square">
            <Wifi />
          </div>
        </template>
        </MenuItem>
      </RouterLink>
      <div class="w-full h-[1px] bg-dark-500/50"></div>
      <LoadingLine v-if="!nearWifi.length"></LoadingLine>
      <div v-else>
        <template v-for="wifi in nearWifi">
          <RouterLink :to="{
            name: 'setWifi'
            , force: true,
            state: { id: wifi.ssid }
          }">

            <div class="w-full h-full">
              <MenuItem :label="wifi.ssid">
              <template #icon>
                <div class="h-8 aspect-square" :style="{
                  opacity: wifiUtlis.rssiToPercent(wifi.rssi) + '%'
                }">
                  <Wifi />
                </div>
              </template>
              </MenuItem>

            </div>
          </RouterLink>
        </template>

        <RouterLink :to="{
          name: 'setWifi'
          , force: true,
          state: { ssid: undefined }
        }">

          <div class="w-full h-full">
            <MenuItem label="Thêm mạng" detail="Nhập thủ công">
            <template #icon>
              <div class="h-8 aspect-square">
                <Plus />
              </div>
            </template>
            </MenuItem>

          </div>
        </RouterLink>
      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
