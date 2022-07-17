/*
CH-231-1
problem4.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    // declaring string vector
    vector<string> word_list;
    // variable to take input from user
    string word = "";
    do
    {
        cin >> word;
        if (word != "END")
        {
            // adding a word into vector
            word_list.push_back(word);
        }

    } while (word != "END");
    // printing contents of vector
    for (int i = 0; i < word_list.size(); i++)
    {
        cout << word_list[i] << " ";
    }
    cout << endl;

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
            cout << *pos << ", ";
        }
    }

    return 0;
}