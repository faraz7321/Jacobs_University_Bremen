const selectMenu = document.getElementById("select");
const options = new Array(500)
  .fill()
  .reduce(
    (html, _, i) => (html += `<option value=${i + 1}>${i + 1}</option>`),
    ""
  );
selectMenu.innerHTML = options;

const selectMenus = document.getElementById("tick");
const option = new Array(10)
  .fill()
  .reduce(
    (html, _, i) => (html += `<option value=${i + 1}>${i + 1}</option>`),
    ""
  );
selectMenus.innerHTML = option;

function process() {
  const fileInput = document.getElementById("file1");
  const file = fileInput.files[0];
  const reader = new FileReader();

  reader.onload = function (event) {
    // Process the file content here
    console.log(event.target.result);
  };

  reader.readAsText(file);
}

const worldMap = document.getElementById("file1");
const redBug = document.getElementById("file2");
const blackBug = document.getElementById("file3");
const iterationsSelect = document.getElementById("select");
const log = document.getElementById("checkbox");
const nextButton = document.getElementById("button");

let map = file1.value;
let redBugSource = file2.value;
let blackBugSource = file3.value;
let iterations = log.value;
let logEnabled = false;
