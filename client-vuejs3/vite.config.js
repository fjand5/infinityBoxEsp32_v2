import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue()],
  build: {
  
    rollupOptions: {
      output: {
        assetFileNames: 'css/[name].[ext]',
        chunkFileNames: 'js/[name].js',
        entryFileNames: 'js/app.js'
      }
    },
    sourcemap: false,
    target: 'esnext'
  }

})
