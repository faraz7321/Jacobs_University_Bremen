// default hardcoded for now, but later we will add tests for files uploaded
test('should create world from string of map', () => {
    const mapData =
        '10\n' +
        '10\n' +
        '# # # # # # # # # #\n' +
        '# 9 9 . . . . 3 3 #\n' +
        '# 9 # . - - - - - #\n' +
        '# . # - - - - - - #\n' +
        '# . . 5 - - - - - #\n' +
        '# + + + + + 5 . . #\n' +
        '# + + + + + + # . #\n' +
        '# + + + + + . # 9 #\n' +
        '# 3 3 . . . . 9 9 #\n' +
        '# # # # # # # # # #\n'

    const world = {
        width: 0,
        height: 0,
        cells: [],
    }

    const map = mapData.split('\n').map(row => row.split(' '))
    const width = +map[0][0]
    const height = +map[1][0]

    // update world
    world.width = width
    world.height = height

    // # obstacle
    // . empty cell (ie, no bug)
    // - empty cell, black swarm nest
    // + empty cell, red swarm nest
    // 1..9 empty cell with number of food units

    // reset cells
    world.cells = []

    // create cells
    for (let i = 0; i < height; i++) {
        for (let j = 0; j < width; j++) {
            const cell = map[i + 2][j]
            switch (cell) {
                case '#':
                    world.cells.push({
                        type: 'obstacle',
                    })
                    break
                case '.':
                    world.cells.push({
                        type: 'empty',
                    })
                    break
                case '-':
                    world.cells.push({
                        type: 'black-nest',
                    })
                    break
                case '+':
                    world.cells.push({
                        type: 'red-nest',
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
                    world.cells.push({
                        type: 'food',
                    })
                    break
                default:
                    world.cells.push({
                        type: 'empty',
                    })
                    break
            }
        }
    }

    // width should be 10
    expect(world.width).toBe(10)

    // height should be 10
    expect(world.height).toBe(10)

    // cells should be 100
    expect(world.cells.length).toBe(100)

    // first cell should be obstacle
    expect(world.cells[0].type).toBe('obstacle')
})
