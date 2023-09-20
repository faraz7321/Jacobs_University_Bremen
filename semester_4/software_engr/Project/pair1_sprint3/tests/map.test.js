const {parseMap} = require('../utils.js');

// valid map
const mapData1 = '10\n' +
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
'# # # # # # # # # #';

// here is length error
const mapData2 = '10\n' +
'11\n' +
'# # # # # # # # # #\n' +
'# 9 9 . . . . 3 3 #\n' +
'# 9 # . . . . . . #\n' +
'# . # . . . . . . #\n' +
'# . . 5 . . . . . #\n' +
'# + + + + + 5 . . #\n' +
'# + + + + + + # . #\n' +
'# + + + + + . # 9 #\n' +
'# 3 3 . . . . 9 9 #\n' +
'# # # # # # # # # #'

// map array error
const mapData3 = '10\n' +
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
'# # # # # # # # #';

// invalid character
const mapData4 = '10\n' +
'10\n' +
'# # # # # # $ # # #\n' +
'# 9 9 . . . . 3 3 #\n' +
'# 9 # . - - - - - #\n' +
'# . # - - - - - - #\n' +
'# . . 5 - - - - - #\n' +
'# + + + + + 5 . . #\n' +
'# + + + + + + # . #\n' +
'# + + + + + . # 9 #\n' +
'# 3 3 . . . . 9 9 #\n' +
'# # # # # # # # # #';

describe('testing map parser function', () => {
    test('should return object with width, height, map and totalFood', () => {
        const map = parseMap(mapData1);
        expect(map).toHaveProperty('width');
        expect(map).toHaveProperty('height');
        expect(map).toHaveProperty('map');
        expect(map).toHaveProperty('totalFood');
    });

    test('should return object with width 10', () => {
        const map = parseMap(mapData1);
        expect(map.width).toBe(10);
    });

    test('should return object with height 10', () => {
        const map = parseMap(mapData1);
        expect(map.height).toBe(10);
    });
    
    test('should throw error if map height is invalid', () => {
        expect(() => parseMap(mapData2)).toThrow('Invalid map height');
    });

    test('should throw error if map width is invalid ', () => {
        expect(() => parseMap(mapData3)).toThrow('Invalid map width');
    });

    test('should throw error if there is invalid character', () => {
        expect(() => parseMap(mapData4)).toThrow('Invalid map characters');
    });

    test('should return object with totalFood 18', () => {
        const map = parseMap(mapData1);
        expect(map.totalFood).toBe(76);
    }   );
});