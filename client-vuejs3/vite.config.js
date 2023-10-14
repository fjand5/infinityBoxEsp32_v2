import { defineConfig } from 'vite'
import { fileURLToPath, URL } from 'node:url'

import vue from '@vitejs/plugin-vue'
import { viteSingleFile } from "vite-plugin-singlefile"

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue()],
  resolve: {
    alias: {
      '~': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
  build: {
  
    rollupOptions: {
      output: {
        // assetFileNames: 'css/[name].[ext]',
        // chunkFileNames: 'js/[name].js',
        // entryFileNames: 'js/app.js'

        manualChunks: false,
        inlineDynamicImports: true,
        entryFileNames: 'js/app.js',   // currently does not work for the legacy bundle
        assetFileNames: 'css/[name].[ext]', // currently does not work for images
      }
    },
    sourcemap: false,
    target: 'esnext'
  }

})
