import { Game } from './logic/Game'
import './styles.css'

const cellDiv = document.createElement('div') as HTMLDivElement
cellDiv.classList.add('cell')

const game = new Game()

// document on load
document.addEventListener('DOMContentLoaded', () => {
    // save game to local storage before unload
    window.addEventListener('beforeunload', () => {
        localStorage.setItem('game', JSON.stringify(game))
    })

    // load game from local storage
    const gameFromLocalStorage = localStorage.getItem('game')

    if (gameFromLocalStorage) {
        const parsedGame = JSON.parse(gameFromLocalStorage)

        try {
            game.setMapData(parsedGame.mapData)
            game.setBugTeam1Data(parsedGame.bugTeam1Data)
            game.setBugTeam2Data(parsedGame.bugTeam2Data)
            game.setIterations(
                +parsedGame.iterations < 100 ? 100 : parsedGame.iterations
            )
            game.setLogResults(parsedGame.logResults)
            game.setState(parsedGame.state)
            game.setWorld(parsedGame.world)
            game.setBugTeam1Color(parsedGame.bugTeam1Color)
            game.setBugTeam2Color(parsedGame.bugTeam2Color)
            game.setFps(parsedGame.fps)
            game.setCurrentIteration(parsedGame.currentIteration)
            game.setLogs(parsedGame.logs)
        } catch (error) {
            console.error(error)
        }
    }

    if (
        window.location.pathname.includes('index.html') ||
        window.location.pathname === '/'
    ) {
        const startGameButton = document.getElementById('start-game-button')

        startGameButton.addEventListener('click', () => {
            game.setState('start')
        })
    }

    if (window.location.pathname.includes('settings.html')) {
        const finishSetupButton = document.getElementById(
            'finish-setup-button'
        ) as HTMLButtonElement
        const worldMapFile = document.getElementById(
            'world-map-file'
        ) as HTMLInputElement
        const bugTeam1File = document.getElementById(
            'bug-team-1-file'
        ) as HTMLInputElement
        const bugTeam2File = document.getElementById(
            'bug-team-2-file'
        ) as HTMLInputElement
        const iterationsSelect = document.getElementById(
            'iterations-select'
        ) as HTMLSelectElement
        const logResultsCheckbox = document.getElementById(
            'log-results-checkbox'
        ) as HTMLInputElement

        worldMapFile.addEventListener('change', event => {
            // read from file
            const file = (event.target as HTMLInputElement).files[0]
            const reader = new FileReader()

            reader.onload = event => {
                const fileContent = event.target.result as string

                game.setMapData(fileContent)
            }

            reader.readAsText(file)
        })

        bugTeam1File.addEventListener('change', event => {
            const file = (event.target as HTMLInputElement).files[0]
            const reader = new FileReader()

            reader.onload = event => {
                const fileContent = event.target.result as string

                game.setBugTeam1Data(fileContent)
            }

            reader.readAsText(file)
        })

        bugTeam2File.addEventListener('change', event => {
            const file = (event.target as HTMLInputElement).files[0]
            const reader = new FileReader()

            reader.onload = event => {
                const fileContent = event.target.result as string

                game.setBugTeam2Data(fileContent)
            }

            reader.readAsText(file)
        })

        iterationsSelect.addEventListener('change', event => {
            const iterations = (event.target as HTMLInputElement).value

            game.setIterations(+iterations)
        })

        logResultsCheckbox.addEventListener('change', event => {
            const logResults = (event.target as HTMLInputElement).checked

            game.setLogResults(logResults)
        })

        finishSetupButton.addEventListener('click', () => {
            // save game to local storage
            localStorage.setItem('game', JSON.stringify(game))
        })
    }

    if (window.location.pathname.includes('options.html')) {
        const goBackButton = document.getElementById(
            'go-back-button'
        ) as HTMLButtonElement

        const fpsSelect = document.getElementById(
            'fps-select'
        ) as HTMLSelectElement

        fpsSelect.value = game.fps.toString()

        const bugTeam1ColorSelect = document.getElementById(
            'bug-team-1-color-select'
        ) as HTMLSelectElement

        bugTeam1ColorSelect.value = game.bugTeam1Color

        const bugTeam2ColorSelect = document.getElementById(
            'bug-team-2-color-select'
        ) as HTMLSelectElement

        bugTeam2ColorSelect.value = game.bugTeam2Color

        const iterationsSelect = document.getElementById(
            'iterations-select'
        ) as HTMLSelectElement

        iterationsSelect.value = game.iterations.toString()

        fpsSelect.addEventListener('change', event => {
            const fps = (event.target as HTMLSelectElement).value
            game.setFps(+fps)
        })

        bugTeam1ColorSelect.addEventListener('change', event => {
            const color = (event.target as HTMLSelectElement).value
            game.setBugTeam1Color(color)
        })

        bugTeam2ColorSelect.addEventListener('change', event => {
            const color = (event.target as HTMLSelectElement).value
            game.setBugTeam2Color(color)
        })

        iterationsSelect.addEventListener('change', event => {
            const iterations = (event.target as HTMLSelectElement).value
            game.setIterations(+iterations)
        })

        goBackButton.addEventListener('click', () => {
            // save game to local storage
            localStorage.setItem('game', JSON.stringify(game))
        })
    }

    if (window.location.pathname.includes('home.html')) {
        const logSwitch = document.getElementById(
            'log-switch'
        ) as HTMLInputElement

        const logsList = document.getElementById('logs') as HTMLDivElement

        logSwitch.addEventListener('change', () => {
            logsList.style.display = logSwitch.checked ? 'block' : 'none'
        })

        const clearLogsButton = document.getElementById(
            'clear-logs-button'
        ) as HTMLButtonElement

        clearLogsButton.addEventListener('click', () => {
            logsList.innerHTML = ''
        })

        const maxIteration = document.getElementById(
            'max-iteration'
        ) as HTMLSpanElement

        maxIteration.innerText = game.iterations.toString()

        const currentIterationSpan = document.getElementById(
            'current-iteration'
        ) as HTMLSpanElement

        const gameField = document.getElementById(
            'game-field'
        ) as HTMLDivElement

        gameField.innerHTML = ''

        // set gameField display to grid
        gameField.style.display = 'grid'

        let gameFieldWidth = gameField.clientWidth
        let gameFieldHeight = gameField.clientHeight

        // update data on gameField resize
        window.addEventListener('resize', () => {
            gameFieldWidth = gameField.clientWidth
            gameFieldHeight = gameField.clientHeight
        })

        const updateGameField = () => {
            // update gameField display
            gameField.style.gridTemplateColumns = `repeat(${game.world.width}, 1fr)`
            gameField.style.gridTemplateRows = `repeat(${game.world.height}, 1fr)`

            // remove all children
            while (gameField.firstChild) {
                gameField.removeChild(gameField.firstChild)
            }

            // create cells
            for (let i = 0; i < game.world.height; i++) {
                for (let j = 0; j < game.world.width; j++) {
                    const newCell = cellDiv.cloneNode() as HTMLDivElement

                    newCell.style.width = `${
                        gameFieldWidth / game.world.width - 10
                    }px`
                    newCell.style.height = `${
                        gameFieldHeight / game.world.height - 10
                    }px`

                    // set cell type
                    const cell = game.world.cells[i * game.world.width + j]
                    newCell.classList.add(cell?.type)

                    gameField.appendChild(newCell)
                }
            }
        }

        const renderIteration = () => {
            currentIterationSpan.innerText = game.currentIteration.toString()

            if (game.iterations <= game.currentIteration) {
                game.setState('end')
                return
            } else {
                game.setState('start')
            }

            updateGameField()

            game.currentIteration += 1

            // save game to local storage
            localStorage.setItem('game', JSON.stringify(game))
        }

        const fps = game.fps ?? 100

        setInterval(() => {
            renderIteration()
        }, 1000 / fps)
    }

    if (window.location.pathname.includes('end.html')) {
        const restartButton = document.getElementById(
            'restart-button'
        ) as HTMLButtonElement

        restartButton.addEventListener('click', () => {
            game.restart()
        })
    }
})
