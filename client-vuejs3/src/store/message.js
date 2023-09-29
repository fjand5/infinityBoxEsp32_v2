import { defineStore } from 'pinia'

export default defineStore('message', {
  state: () => ({
    message: undefined
  }),
  actions: {
    addMessage (text, type = 'ERROR', time = 3) {
      this.message = { text, type, time }
    },
    clearMessage () {
      this.message = undefined
    }
  }
})
