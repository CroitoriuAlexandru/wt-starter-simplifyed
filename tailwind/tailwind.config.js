/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "../xml-templates/**/*.xml", 
    "../src/**/*.{cpp,hpp,h}",
    "../src/**/**/*.{cpp,hpp,h}",
    "../src/**/**/**/*.{cpp,hpp,h}",
  ],
  theme: {
    extend: {
    },
  },
  plugins: [],
}