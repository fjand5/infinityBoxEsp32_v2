import { defineStore } from 'pinia'
import useMessageStore from './message'
import { MetaApi, ContentApi } from '../api'
export default defineStore('wifiSetup', {
  state: () => ({
    meta: {
      wifi: {},
      content: {
        shadow: '',
        screen:''
      }
    }
  }),
  actions: {
    async commitShadow (shadow) {
      const json = await ContentApi.setShadow(shadow)
      this.meta.content['shadow'] = json['newValue']
    },
    async commitApSSID (apSSID) {
      const json = await MetaApi.setApSSID(apSSID)
      this.meta.wifi['ApSSID'] = json['newValue']
      useMessageStore().addMessage(
        `Hoàn Thành`,
        'SUCCESS',
        4
      )
    },
    async commitApPASS (apPASS) {
      const json = await MetaApi.setApPASS(apPASS)
      this.meta.wifi['ApPASS'] = json['newValue']
      useMessageStore().addMessage(
        `Hoàn Thành`,
        'SUCCESS',
        4
      )
    },
    async commitStaSSID (staSSID) {
      const json = await MetaApi.setStaSSID(staSSID)
      this.meta.wifi['staSSID'] = json['newValue']
    },
    async commitStaPASS (staPASS) {
      const json = await MetaApi.setStaPASS(staPASS)
      this.meta.wifi['staPASS'] = json['newValue']
    },
    async loadMetaData () {
      const wifiData = await MetaApi.getWifi()
      const contentData = await ContentApi.getContent()
      const tmp = {}
      tmp.wifi = wifiData
      tmp.content = contentData
      this.meta = JSON.parse(JSON.stringify(tmp))
    }
  }
})
