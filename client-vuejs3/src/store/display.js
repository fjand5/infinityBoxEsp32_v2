import { defineStore } from 'pinia'
import useMessageStore from './message'
import { DisplayApi} from '../api'
export default defineStore('display', {
  state: () => ({
      brightness: 0,
      chainedType: "",
      autoBrightness: false
  }),
  actions: {
    async loadDisplayData () {
      const displayData = await DisplayApi.getDisplay()
      this.brightness = displayData['brightness']
      this.chainedType = displayData['chainedType']
      this.autoBrightness = displayData['autoBrightness']
    }
  }
})
