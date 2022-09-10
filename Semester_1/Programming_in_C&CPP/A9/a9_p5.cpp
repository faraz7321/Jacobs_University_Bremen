/*
CH-230-A
a9_p5.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    int die;
    int input;
    int randomNumber;
    // init random number generator
    system("cls");
    srand(static_cast<unsigned int>(time(0)));
    do
    {
        cout << "I rolled a dice, guess whats on top." << endl;

        cin >> input;
        randomNumber = rand();
        die = (randomNumber % 6) + 1;
        if (input == die)
        {
            cout << "yayy you guessed it right!!!" << endl;
        }
        else
        {
            cout << "nah you guessed that wrong.\nit was " << die << endl;
        }
        cout << "enter -1 to end game\n";
    } while (input != -1);
    cout << "closing program";

    return 0;
}
