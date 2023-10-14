/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{vue,js,ts,jsx,tsx}'],
  theme: {
    extend: {
      colors: {
        dark: {
          100: '#212121',
          200: '#424242',
          300: '#FFF07A',
          400: '#FFE0B2',
          500: '#ECEFF1'
        }
      }
    }
  },
  plugins: []
}
