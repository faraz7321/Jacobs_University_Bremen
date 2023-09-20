// on doc ready
$(function () {

  // classes
  class GUI {
    static screens = [
      "welcome",
      "settings",
      "game",
      "options",
      "quit",
      "restart",
    ];
    static currentScreen = "welcome";

    static alert(text) {
      alert(text);
    }

    static setScreen(newScreen) {
      if (!this.screens.includes(newScreen)) {
        throw new Error("Invalid screen passed in");
      }

      // update the current screen
      this.currentScreen = newScreen;

      // hide all screens except the one passed in
      this.screens.forEach(function (screen) {
        $(`#${screen}-screen`).hide();
      });

      // show the screen passed in
      $(`#${this.currentScreen}-screen`).show();
    }

    static updateStats(stats, currentIteration, totalIterations) {
      // stats dom elements
      const gameStatsIterations = $("#game-stats-iterations");
      const gameStatsFoods = $("#game-stats-food");
      const gameStatsTeam1Alive = $("#game-stats-bug-team-1-alive");
      const gameStatsTeam2Alive = $("#game-stats-bug-team-2-alive");
      const gameStatsTeam1Killed = $("#game-stats-bug-team-1-killed");
      const gameStatsTeam2Killed = $("#game-stats-bug-team-2-killed");
      const gameStatsTeam1Food = $("#game-stats-bug-team-1-food");
      const gameStatsTeam2Food = $("#game-stats-bug-team-2-food");

      // game iterations
      gameStatsIterations.text(`${currentIteration}/${totalIterations}`);

      // game food stat
      gameStatsFoods.text(stats.totalFood);

      // update the team stats
      const { bugTeam1, bugTeam2 } = stats;
      gameStatsTeam1Alive.text(bugTeam1.alive);
      gameStatsTeam2Alive.text(bugTeam2.alive);
      gameStatsTeam1Killed.text(bugTeam1.killed);
      gameStatsTeam2Killed.text(bugTeam2.killed);
      gameStatsTeam1Food.text(bugTeam1.food);
      gameStatsTeam2Food.text(bugTeam2.food);
    }

    static log(log) {
      const sessionLogsElement = $("#session-logs");
      sessionLogsElement.empty();

      sessionLogsElement.append(`<div class="log">${log}</div>`);
    }

    static updateMap(map) {
      const gameField = $("#game-field");
      gameField.empty();

      // get width of the div in pixels
      const width = gameField.width();
      const height = gameField.height();

      const hexWidth = width / map[0].length;
      const hexHeight = height / map.length;

      map.forEach(function (row, rowIndex) {
        const rowElement = $("<div class='hex-row'></div>");

        row.forEach(function (cell, cellIndex) {
          const cellElement = $("<div class='hex-cell'></div>");
          cellElement.addClass(`game-map-cell-${rowIndex}-${cellIndex}`);
          cellElement.css("width", `${hexWidth}px`);
          cellElement.css("height", `${hexHeight}px`);  

          // # – obstacle
          // . – empty cell (ie, no bug) - empty cell
          // - – black swarm nest
          // + – empty cell, red swarm nest 
          // 1..9 empty cell with number of food units
          
          switch (cell) {
            case "#":
              cellElement.addClass("obstacle-cell");
              cellElement.append('<img src="images/rocks.png" />')
              break;
            case ".":
              cellElement.addClass("empty-cell");
              // cellElement.append('<img src="images/empty.png" />')
              break;
            case "-":
              cellElement.addClass("team-1-nest");
              cellElement.append('<img src="images/bug1.png"/>')
              break;
            case "+":
              cellElement.addClass("team-2-nest");
              cellElement.append('<img src="images/bug2.png" />')
              break;
            default:
              cellElement.addClass("empty-cell");
              // cellElement.append('<img src="images/empty.png" class="rock-img" />')
              break;
          }

          if(cell.match(/[1-9]/)) {
            cellElement.addClass(`food-cell-${cell}`);
            cellElement.append(`<img src="images/food.png" />`)
          }

          // cellElement.text(cell);

          rowElement.append(cellElement);
        });

        gameField.append(rowElement);
      });
    }

  }

  class Game {
    constructor() {
      this.map = null;
      this.bugTeam1 = null;
      this.bugTeam2 = null;
      this.totalIterations = 0;
      this.currentIteration = 0;
      this.tickSpeed = 0;
      this.stats = {
        totalFood: 0,
        bugTeam1: {
          alive: 0,
          killed: 0,
          food: 0,
        },
        bugTeam2: {
          alive: 0,
          killed: 0,
          food: 0,
        },
      };
      this.sessionLogs = [];
    }

    setMap(map) {
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

      // count all the food
      const totalFood = flatMapArray.reduce(function (total, character) {
        if (character.match(/[1-9]/)) {
          return total + parseInt(character);
        }
        return total;
      }, 0);

      this.stats.totalFood = totalFood;

      this.map = mapArray;
    }

    setBugTeam1(bugTeam1) {
      this.bugTeam1 = bugTeam1;
    }

    setBugTeam2(bugTeam2) {
      this.bugTeam2 = bugTeam2;
    }

    setTotalIterations(iterations) {
      if (isNaN(iterations) || iterations === "" || iterations === null) {
        throw new Error("Please enter a total number of iterations");
      }

      this.totalIterations = iterations;
    }

    setTickSpeed(tickSpeed) {
      this.tickSpeed = tickSpeed;
    }

    // tickSpeed frames per second
    start() {
      // start the iterations
      const interval = setInterval(() => {
        // check if the game is over
        if (this.currentIteration >= this.totalIterations) {
          clearInterval(interval);
          GUI.alert("Game over")
          return;
        }

        // run the iteration
        this.render();

        // increment the current iteration
        this.currentIteration++;
      }, 1000 / this.tickSpeed);
    }   

    render() {
      GUI.updateStats(this.stats, this.currentIteration, this.totalIterations);
      GUI.updateMap(this.map);
    }
  } 

  // globals
  const game = new Game();

  // dom elements
  const startBtn = $("#start-btn");

  const settingsForm = $("#settings-form");

  const gameMapInput = $("#game-map-input");
  const bugTeam1Input = $("#bug-team-1-input");
  const bugTeam2Input = $("#bug-team-2-input");
  const totalIterationsInput = $("#total-iterations-input");
  const tickSpeedInput = $("#tick-speed-input");

  const optionsOpenBtn = $("#options-open-btn");
  const optionsCloseBtn = $("#options-close-btn");
  const saveBtn = $("#save-btn");

  const quitBtn = $("#quit-btn");
  const quitYesBtn = $("#quit-yes-btn");
  const quitNoBtn = $("#quit-no-btn");

  const restartBtn = $("#restart-btn");

  const sessionLogs = $("#session-logs");


  // listeners
  startBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("settings");
  });

  optionsOpenBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("options");
  });

  optionsCloseBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("game");
  });

  saveBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("game");
  });

  quitBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("quit");
  });

  quitYesBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("restart");
  });

  quitNoBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("game");
  });

  restartBtn.on("click", function (event) {
    event.preventDefault();
    GUI.setScreen("welcome");
  });

  settingsForm.on("submit", function (event) {
    event.preventDefault();
    // get the values from the form

    // read file from input
    if (gameMapInput[0].files.length === 0) {
      alert("Please select a map file");
      return;
    }
    const mapFile = gameMapInput[0].files[0];

    if (bugTeam1Input[0].files.length === 0) {
      alert("Please select a bug team 1 file");
      return;
    }

    const bugTeam1File = bugTeam1Input[0].files[0];

    // read file from input
    if (bugTeam2Input[0].files.length === 0) {
      alert("Please select a bug team 2 file");
      return;
    }

    const bugTeam2File = bugTeam2Input[0].files[0];

    const totalIterations = totalIterationsInput.val();
    if (totalIterations === "") {
      alert("Please enter a total number of iterations");
      return;
    }

    const tickSpeed = tickSpeedInput.val();
    if (tickSpeed === "") {
      alert("Please enter a tick speed");
      return;
    }

    // read the files
    const mapReader = new FileReader();
    mapReader.onload = function (event) {
      const map = event.target.result;
      try {
        game.setMap(map);
      } catch (error) {
        alert(error.message);
        return;
      }
    };
    mapReader.readAsText(mapFile);

    const bugTeam1Reader = new FileReader();
    bugTeam1Reader.onload = function (event) {
      const bugTeam1 = event.target.result;
      game.setBugTeam1(bugTeam1);
    };

    bugTeam1Reader.readAsText(bugTeam1File);

    const bugTeam2Reader = new FileReader();
    bugTeam2Reader.onload = function (event) {
      const bugTeam2 = event.target.result;
      game.setBugTeam2(bugTeam2);
    };

    bugTeam2Reader.readAsText(bugTeam2File);

    try {
      game.setTotalIterations(totalIterationsInput.val());
      game.setTickSpeed(tickSpeedInput.val());
    } catch (error) {
      alert(error.message);
      return;
    }

    GUI.setScreen("game");

    game.start();
  });

});
