/** @type {import('tailwindcss').Config} */
module.exports = {
    jit: true,
    purge: ['./src/**/*.html', './src/**/*.{js,ts}'],
    content: ['./src/**/*.{html,ts}'],
    theme: {
        extend: {},
    },
    plugins: [],
}
