/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{vue,js,ts,jsx,tsx}'],
  theme: {
    extend: {
      colors: {
        led: {
          100: '#08085E',
          200: '#A2EF44',
          300: '#FFF07A',
          400: '#E8FCF6',
          500: '#FC2947'
        }
      }
    }
  },
  plugins: []
}
