/*
CH-230-A
a9_p9.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
using namespace std;
string replace(string word);
void quit();
int main()
{
    string input;
    int index;
    // declaring a string of total of 17 words
    string words[] = {"computer",
                      "television",
                      "keyboard",
                      "laptop",
                      "mouse",
                      "submit",
                      "solution",
                      "program",
                      "jacobs",
                      "university",
                      "science",
                      "technology",
                      "games",
                      "programming",
                      "mobile",
                      "headphones",
                      "germany"};

    srand(static_cast<unsigned int>(time(0)));
    do
    {

        index = (rand() % 17); // generating random number from 0 to 16
        cout << "Guess the following word or enter \"quit\" to end game:\n"
             << replace(words[index]) << endl;

        getline(cin, input); // taking guess from user

        // checking if the guess was correct
        if (input == "quit")
        {
            quit();
        }
        if (input == words[index])
        {
            cout << "You guessed that right!\n";
        }
        else
        {
            cout << "oh no you guessed that wrong!\n"
                 << "it was "
                 << words[index] << endl;
        }
    } while (input != "quit");
    cout << endl;
    return 0;
}
/**
 * @brief replaces vowels with underscores
 *
 * @param word
 * @return string
 */
string replace(string word)
{
    string replaced = word;
    int len = replaced.size();
    bool isVowel;
    for (int i = 0; i < len; i++)
    {
        isVowel = (word[i] == 'a' || replaced[i] == 'e' || replaced[i] == 'i' || replaced[i] == 'o' || replaced[i] == 'u');
        if (isVowel)
        {
            replaced[i] = '_';
        }
    }
    return replaced;
}
/**
 * @brief end program
 *
 */
void quit()
{
    cout << "bubye!\n";
    exit(0);
}