const baseUrl = import.meta.env.PROD
  ? import.meta.env.VITE_BASE_URL_PRO
  : import.meta.env.VITE_BASE_URL_DEV
export default baseUrl;