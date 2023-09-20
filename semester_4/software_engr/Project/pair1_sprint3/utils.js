function parseMap(map) {
  const lines = map.split("\n");
  const width = parseInt(lines[0]);
  const height = parseInt(lines[1]);
  const mapLines = lines.slice(2);

  if (mapLines.length !== height) {
    throw new Error("Invalid map height");
  }

  const mapArray = [];

  mapLines.forEach(function (line) {
    const lineArray = line.split(" ");
    if (lineArray.length !== width) {
      throw new Error("Invalid map width");
    }
    mapArray.push(lineArray);
  });

  const flatMapArray = mapArray.flat();
  const allowedCharactes = [
    "#",
    "+",
    "-",
    ".",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
  ];

  const hasInvalidCharacters = flatMapArray.some(function (character) {
    return !allowedCharactes.includes(character);
  });

  if (hasInvalidCharacters) {
    throw new Error("Invalid map characters");
  }

  const totalFood = flatMapArray.reduce(function (total, character) {
    if (character.match(/[1-9]/)) {
      return total + parseInt(character);
    }
    return total;
  }, 0);

  return {
    width,
    height,
    map: mapArray,
    totalFood
  };
}


module.exports = {
    parseMap
}