import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import WiFiView from '~/views/WiFiView.vue'
import SetWiFiView from '~/views/SetWiFiView.vue'
import SystemView from '~/views/SystemView.vue'
import MicrophoneView from '~/views/MicrophoneView.vue'

const router = createRouter({
  mode: 'history',

  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView
    },
    {
      path: '/wifi',
      name: 'wifi',
      component: WiFiView
    },
    {
      path: '/setWifi',
      name: 'setWifi',
      component: SetWiFiView
    },
    {
      path: '/system',
      name: 'system',
      component: SystemView
    },
    {
      path: '/microphone',
      name: 'microphone',
      component: MicrophoneView
    },
    { path: '/:pathMatch(.*)*', component: HomeView }
  ]
})

export default router
