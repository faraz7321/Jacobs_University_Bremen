/*
CH-231-1
problem5.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// print functions
void print(vector<string>, string);
void print_iter(vector<string>, string);
void print_rev(vector<string>, string);
int main()
{
    vector<string> word_list; // vector
    // variable to take input from user
    string word = "";
    do
    {
        getline(cin, word);
        if (word != "END")
        {
            // adding a word into vector
            word_list.push_back(word);
        }

    } while (word != "END");

    // swap elements at index 1 and 4
    if (word_list.size() >= 4)
    {
        iter_swap(word_list.begin() + 1, word_list.begin() + 4);
    }
    else
    {
        cout << "one or both of the elements do not exist\n";
    }
    // replacing last element with "???"
    word_list.at(word_list.size() - 1) = "???";
    // print vector
    print(word_list, ", ");
    print_iter(word_list, ";");
    print_rev(word_list, " ");
    return 0;
}
/**
 * @brief print with index operator
 *
 * @param word_list
 * @param sep
 */
void print(vector<string> word_list, string sep)
{
    // printing contents of vector
    for (int i = 0; i < word_list.size(); i++)
    {
        if (i == word_list.size() - 1)
        {
            cout << word_list[i];
        }
        else
        {
            cout << word_list[i] << sep;
        }
    }
    cout << endl;
}
/**
 * @brief print using iterator
 *
 * @param word_list
 * @param sep
 */
void print_iter(vector<string> word_list, string sep)
{
    // Iterator of vecotr
    vector<string>::const_iterator pos;

    // printing contents of vector using iterator
    for (pos = word_list.begin(); pos != word_list.end(); ++pos)
    {
        if (pos == word_list.end() - 1)
        {
            cout << *pos;
        }
        else
        {
            cout << *pos << sep;
        }
    }
    cout << endl;
}
/**
 * @brief print in reverse order
 * and using iterator
 *
 * @param word_list
 * @param sep
 */
void print_rev(vector<string> word_list, string sep)
{
    // Iterate from end to start
    for (auto it = word_list.rbegin(); it != word_list.rend(); it++)
    {
        // Print each element
        cout << *it << sep;
    }
    cout << endl;
}