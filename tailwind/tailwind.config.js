/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    // "../xml-templates/**/*.xml", 
    // "../src/**/*.{cpp,hpp,h}",
    // "../src/**/**/*.{cpp,hpp,h}",
    // "../src/**/**/**/*.{cpp,hpp,h}",
  ],
  theme: {
    extend: {
    },
  },
  plugins: [
    require("./local_plugins/tailwindcss-question-mark-double")({
      animationDuration: "0.6s",
      enableAnimation: true,
      highlightColorStart: "#6BF193",
      highlightColorEnd: "#1FF760",
      widthStart: "4px",
      widthEnd: "6px",
    }),
    require("./local_plugins/tailwindcss-question-mark")({
      animationDuration: "0.6s",
      enableAnimation: true,
      highlightColorStart: "#f16bc9",
      highlightColorEnd: "#f71fb6",
      widthStart: "4px",
      widthEnd: "6px",
    }),
  ],
}