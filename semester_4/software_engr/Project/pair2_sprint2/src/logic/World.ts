export type IWorld = {
    width: number
    height: number
    cells: ICell[]
}

export enum CellType {
    Empty = 'empty',
    Obstacle = 'obstacle',
    BlackNest = 'black-nest',
    RedNest = 'red-nest',
    Food = 'food',
}

type ICell = {
    type: CellType
}

export class World implements IWorld {
    width: number
    height: number
    cells: ICell[]

    constructor(width: number, height: number) {
        this.width = width
        this.height = height
        this.cells = []

        for (let i = 0; i < height; i++) {
            for (let j = 0; j < width; j++) {
                this.cells.push({
                    type: CellType.Empty,
                })
            }
        }
    }

    setWidth(width: number) {
        this.width = width
    }

    setHeight(height: number) {
        this.height = height
    }

    setCells(cells: ICell[]) {
        this.cells = cells
    }
}

export {}
