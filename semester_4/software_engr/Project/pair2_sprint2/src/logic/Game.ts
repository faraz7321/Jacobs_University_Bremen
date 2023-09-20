import { CellType, IWorld, World } from './World'

type IGameState = 'initial' | 'start' | 'pause' | 'end'

type ILog = {
    text: string
    time?: string
}

type IGame = {
    mapData: string
    bugTeam1: string
    bugTeam2: string
    iterations: number
    logResults: boolean
    state: IGameState
    world: IWorld
    bugTeam1Color: string
    bugTeam2Color: string
    fps: number
    currentIteration: number
    logs: ILog[]
}

// @ts-expect-error fix
export class Game implements IGame {
    mapData: string
    bugTeam1Data: string
    bugTeam2Data: string
    iterations: number
    logResults: boolean
    state: IGameState
    world: IWorld
    bugTeam1Color: string
    bugTeam2Color: string
    fps: number
    currentIteration: number
    logs: ILog[]

    constructor() {
        this.mapData = ''
        this.bugTeam1Data = ''
        this.bugTeam2Data = ''
        this.iterations = 0
        this.logResults = false
        this.state = 'initial'
        this.world = new World(0, 0)
        this.bugTeam1Color = 'red'
        this.bugTeam2Color = 'black'
        this.fps = 1
        this.currentIteration = 0
        this.logs = []
    }

    setMapData(mapData: string) {
        this.mapData = mapData

        try {
            this.createWorld()
        } catch (error) {
            console.log(error)
        }
    }

    createWorld() {
        const map = this.mapData.split('\n').map(row => row.split(' '))
        const width = +map[0][0]
        const height = +map[1][0]

        // update world
        this.world.width = width
        this.world.height = height

        // # obstacle
        // . empty cell (ie, no bug)
        // - empty cell, black swarm nest
        // + empty cell, red swarm nest
        // 1..9 empty cell with number of food units

        // reset cells
        this.world.cells = []

        // create cells
        for (let i = 0; i < height; i++) {
            for (let j = 0; j < width; j++) {
                const cell = map[i + 2][j]
                switch (cell) {
                    case '#':
                        this.world.cells.push({
                            type: CellType.Obstacle,
                        })
                        break
                    case '.':
                        this.world.cells.push({
                            type: CellType.Empty,
                        })
                        break
                    case '-':
                        this.world.cells.push({
                            type: CellType.BlackNest,
                        })
                        break
                    case '+':
                        this.world.cells.push({
                            type: CellType.RedNest,
                        })
                        break
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        this.world.cells.push({
                            type: CellType.Food,
                        })
                        break
                    default:
                        console.log(cell)
                        console.log('unknown cell type')
                        this.world.cells.push({
                            type: CellType.Empty,
                        })
                        break
                }
            }
        }
    }

    setBugTeam1Data(bugTeam1Data: string) {
        this.bugTeam1Data = bugTeam1Data
    }

    setBugTeam2Data(bugTeam2Data: string) {
        this.bugTeam2Data = bugTeam2Data
    }

    setIterations(iterations: number) {
        this.iterations = iterations
    }

    setLogResults(logResults: boolean) {
        this.logResults = logResults
    }

    setState(state: IGameState) {
        this.state = state
    }

    setWorld(world: IWorld) {
        this.world = world
    }

    setBugTeam1Color(bugTeam1Color: string) {
        this.bugTeam1Color = bugTeam1Color
    }

    setBugTeam2Color(bugTeam2Color: string) {
        this.bugTeam2Color = bugTeam2Color
    }

    setFps(fps: number) {
        this.fps = fps
    }

    setCurrentIteration(currentIteration: number) {
        this.currentIteration = currentIteration
    }

    setLogs(logs: ILog[]) {
        this.logs = logs
    }

    addLog(log: ILog) {
        this.logs.push(log)
    }

    clearLogs() {
        this.logs = []
    }

    restart() {
        this.currentIteration = 0
        this.clearLogs()
        this.setState('initial')
        this.mapData = ''
        this.bugTeam1Data = ''
        this.bugTeam2Data = ''
        this.iterations = 0
        this.logResults = false
        this.world = new World(0, 0)
        this.bugTeam1Color = 'red'
        this.bugTeam2Color = 'black'
        this.fps = 1
    }
}

export {}
