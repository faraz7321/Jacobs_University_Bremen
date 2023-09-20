// Wrong bug input could look like this
// sense_ahead 1 3 food ; [ 0]
// move 2 0 ; [ 1]
// pickup 8 0 ; [ 2]
// flip 3 4 5 ; [ 3]
// turn_left 0 ; [ 4]
// flip 2 6 7 ; [ 5]
// turn_right 0 ; [ 6]
// move 0 3 ; [ 7]
// sense_ahead 9 11 home ; [ 8]
// move 10 8 ; [ 9]
// drop 0 ; [ 10]
// flip 3 12 13 ; [ 11]
// turn_left 8 ; [ 12]
// flip 2 14 15 ; [ 13]
// turn_right 8 ; [ 14]
// move 8 11 ; [ 15]

test('simple bug algorithm to check step by step that everything is correct', () => {
    // TODO: tests
})
