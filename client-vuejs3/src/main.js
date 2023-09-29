import { createApp } from 'vue'
import './style.css'
import App from './App.vue'
import { createPinia } from 'pinia'
// import { PiniaUndo } from 'pinia-undo'
import {Tabs, Tab} from 'vue3-tabs-component';

const pinia = createPinia()
// pinia.use(PiniaUndo)
createApp(App)
.use(pinia)
.component('tabs', Tabs)
.component('tab', Tab)
.mount('#app')
