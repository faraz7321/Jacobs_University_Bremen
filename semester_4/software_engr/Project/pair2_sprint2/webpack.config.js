const path = require('path')
const CopyPlugin = require('copy-webpack-plugin')

module.exports = {
    entry: './src/index.ts',
    mode: 'development',
    module: {
        rules: [
            {
                test: /\.ts$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            },
            {
                test: /\.css$/,
                include: path.resolve(__dirname, 'src'),
                use: ['style-loader', 'css-loader', 'postcss-loader'],
            },
        ],
    },
    devServer: {
        watchFiles: ['src/**/*.{html,ts,css}'],
    },
    resolve: {
        extensions: ['.ts', '.html', '.js', '.css'],
    },
    plugins: [
        new CopyPlugin({
            patterns: [
                { from: 'src/index.html', to: 'index.html' },
                { from: 'src/settings.html', to: 'settings.html' },
                { from: 'src/home.html', to: 'home.html' },
                { from: 'src/options.html', to: 'options.html' },
                { from: 'src/quit.html', to: 'quit.html' },
                { from: 'src/end.html', to: 'end.html' },
                { from: 'src/styles.css', to: 'styles.css' },
            ],
        }),
    ],
    output: {
        filename: 'bundle.js',
        path: path.resolve(__dirname, 'build'),
        clean: true,
    },
}
