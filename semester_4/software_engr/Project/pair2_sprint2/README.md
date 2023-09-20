# Bug World Simulator

## Sprint 1

#### Backend part improvements

-   Implemented all primary classes, such as World, Bug, WorldCell, BugBrain, as well as smaller classes such as Color, Position, Marker and others using JavaScript programming language. Each class has been developed with all necessary fields and primary functions in accordance with Specifications Standard.
-   To ensure clarity where required, documentation has been added in the form of comments that explain the logic of code.
-   Also main classes now have method toString() providing their inner state in user-friendly format for debugging purposes.
-   Added test folder that contains test checking the correct creation of the Bug class and its output in the user-friendly format.\
    To run the test you need to run `node src/test/ToStringTest.js` from project root folder.

#### Frontend (GUI) part improvements

-   The skeleton of the BugWorld game has been created along with all the web pages.
-   Each page has all the required elements besides the "Log" page.
-   All of the buttons in each page work and the user can easily navigate through the pages using them.
-   Since the Java Script and the GUI (html and css) have been done separately(each group member did one each one), therefore they might not look like they are linked together.
-   For the time being, an image of the Bug World has been added instead of the actual working Bug World.
-   The webpage has been hosted in Clamv. Here is the [link](http://clabsql.clamv.jacobs-university.de/~bishrestha/).

---

## Sprint 2 Progress - Kaisar Alibekov and Faraz Ahmad

### What is done so far and improved:

✅ Changed the structure of game logic written in JavaScript to TypeScript (notes below)\
✅ Configured TypeScript classes and interfaces to create game logic and improved the old code because their JS files were not linked with the HTML pages (previous sprint members created separated pages but did not think about transferring the input files between the pages). Basically, their code was not well linked with each other. We were just given a simple frontend.\
✅ Implemented the feature of uploading world map .txt file. The demo is below. You can try to input different example files from "data" folder. So, the game environment is created - walls, food, red and black bugs - according to the colors specified in the document.\
✅ All coding in this repo is done using **SOLID** principles, so please have a look at our TypeScript files. The file hierarchy is simplified and allows you to easily add new pages and functions, thanks to generalized classes and interfaces. Our code is purely object-oriented.\
✅ Linter is added to detect errors while debugging (before committing github)\
✅ Added Tailwind CSS as UIKit to employ css classes\
✅ Set up webpack for optimizing bundle (JavaScript, HTML, CSS)\
✅ Improvements of UI to ensure better user experience\
✅ To transfer the input files between the pages, we used browser's local storage to save files. It also saves game locally.\
✅ Used descriptive variable and function names with appropriate **in-line comments**. We believe it will help future sprinters.\
✅ Configured Jest for tests (below)

### Built with
* HTML
* TailwindCSS
* JavaScript
* TypeScript
* Jest
* Linter
* Webpack
* Husky

### Deployment

#### Locally

-   To start a development server and open the game initial page, run these three commands:\
    `npm install --global yarn`\
    `yarn install `\
    `yarn dev`
-   The main page: http://localhost:3000

#### Github hosting (GitHub Pages)

-   To ease the grading process for TAs, please open this link (not ClamV): https://alibek0v.github.io/bug-world/
-   ClamV does not support yarn and npm. That's why we used GitHub Pages. Official tutorial is here: https://docs.github.com/en/pages/getting-started-with-github-pages/creating-a-github-pages-site , but I will describe the steps now:
-   First, clone the github repo to your profile's repo as we cannot access the settings.
-   Then, run command "yarn build", it will create build folder in project directory. Rename this folder to "docs".
-   git push your repo and go to Settings, on the left, go to Pages tab. Here you can host the website on GitHub.
-   Choose your branch and select /docs folder. Then click "Save". Done! GitHub will give you the link.

### Tests

-   Run this command first: `yarn add --dev jest` to download Jest.

-   To run the tests, use the command `yarn test`. It will run all the test cases in the `tests` folder.

### File Structure (only important files are displayed)

```
\pair2_sprint2
        \.husky                   # package that will enforce that your code runs against a pre-commit check
        \.vscode                  # VSCode extensions
        \coverage                 # Jest code coverage (for tests)
        \data                     # world map .txt example files
        \docs                     # HTML pages for GitHub Pages deployment
        \src
            \logic                # Game.ts and World.ts files for game logic
                \ - ...
            \ - ...               # HTML pages 
        \tests                    # Written tests
            \ - ...
        package.json              # File enabling npm to start project, install dependencies
        \ - other config files
        README.md
        .gitignore  
```

**TypeScript's usage justification:** Essentially, TypeScript is augmented version of JavaScript with more functions, and they are similar. According to the reference design, there are several strict interfaces and classes. TypeScript is more object-oriented so it helps us implement the interfaces described in specification. As we know, JavaScript does not support interfaces. We suppose in this case it is beneficial to use TypeScript because it is suitable and comfortable to implement the logic itself. While executing, the code in web browser will be shown in JavaScript. Arkid is aware of that we used TypeScript.

## Demo
We manually tested different kinds of map .txt files, and our game environment works properly.

![](https://github.com/CU-Software-Engineering-2023/pair2_sprint2/blob/master/demo.gif)
