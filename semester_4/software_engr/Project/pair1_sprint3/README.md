# Bug World Simulator

## Pair1_Sprint2 (Previous sprint)

The program can be found in the following URL:
<http://clabsql.clamv.jacobs-university.de/~vaguilar/SE_Homework2/start.html>

- Test cases were added
- Currently the program is able to take the user input and render the map with the elements read by the .txt map file uploaded by the user
- All classes are created and linked between each other, so all the project architecture and design is ready.
- Inner logic of the game is implemented, e.g all the basic core classe's api is implemented. Provided nessesary relations between classes for implementing assembler.
- All the parts of the code (classes, attributes, functions) have corresponding documentation provided by comments in code.
- It also prints map to user with number of red bugs , black bugs and food.

### Input

```txt
10
10
# # # # # # # # # #
# 9 9 . . . . 3 3 #
# 9 # . . . . . 3 #
# . # . . . . . . #
# . . 5 . . . . . #
# + + + + + 5 . . #
# + + + + + + # . #
# + + + + + . # 9 #
# 3 3 . . . . 9 9 #
# # # # # # # # # #
```

### Output

![Screenshot (178)](https://user-images.githubusercontent.com/71903387/231769716-93bfb2de-9a80-437f-80a0-03e3ae584d14.png)

### Demo

- how it was implemented

![](https://github.com/CU-Software-Engineering-2023/pair1_sprint3/blob/master/demo-old.gif)

---

## Sprint 3 - Kaisar Alibekov and Faraz Ahmad

### What is incorrect with the previous sprint code:

- First of all, their input file is wrong. As you can see, there is no "-" sign for another bug team. Hence, their output is also incorrect because there should not be black color bug team. Moreover, in the output, the input numbers like "9" and "3" are displayed like bugs, but the numbers, actually, are food according to the specification. TAs, please consider that. Thus, it seems that they messed up with the logic and output while setting up the environment.
- Second, the UI is not responsive at all. After the input of .txt file, our website page was not similar to the above example. Proof will be below.

### What is done so far and improved:

✅ Considering our previous feedback from TAs, validation and exception handling for input files/options form was added to ensure the .txt file is correct. Please see it in the code and respective comments. Moreover, browser console will display error messages.\
✅ Fixed their JavaScript code to properly display the world. To display map environment, please use the .txt files from "mockdata" folder. So, the game environment is created - walls, food, red and black bugs - according to the colors specified in the document.\
✅ Regarding the visual component, we managed files in proper folders.\
✅ Added more tests using Jest environment.\
✅ Completely changed the css and html file structure to get rid of UI problems. Now, the GUI is flawless and it is responsive, and more easier to follow.\
✅ Configured JavaScript classes and functions to create game logic. Now it is easy to add new functions and classes, because the code is more generalized. Please view how we wrote our code. The file hierarchy is simplified and allows you to easily add new pages. Our code is purely object-oriented.\
✅ Used descriptive variable and function names with appropriate **in-line comments**. We believe it will help future sprinters.\

### Built with

- HTML
- CSS
- JavaScript
- Jest

### Deployment

#### Locally

- Since the code is pure JS, just go to the project folder and open "index.html" file. It will work with no problems.

#### Github hosting (GitHub Pages)

- Please open this link (not ClamV): https://alibek0v.github.io/bug/
- We used GitHub Pages. Official tutorial is here: https://docs.github.com/en/pages/getting-started-with-github-pages/creating-a-github-pages-site , GitHub Pages will look for an "index.html" as the entry file for your site. Done! GitHub will give you the link.

### Tests

- To run the tests, use the two commands `yarn install` and `yarn test`. It will run all the test cases in the `tests` folder.

```
\pair1_sprint3
        \.vscode                  # VSCode extensions
        \coverage                 # Jest code coverage (for tests)
        \css                      # css files
        \images                   # used images
        \mockdata                 # world map .txt example files
        \js                       # logic is here
        \tests                    # written tests
            \ - ...
        package.json              # file enabling npm to start project, install dependencies
        \ - other config files
        index.html                # Main Page
        README.md
        .gitignore
```

### Demo

We manually tested different kinds of map .txt files, and our game environment works properly.

![](https://github.com/CU-Software-Engineering-2023/pair1_sprint3/blob/master/demo.gif)
