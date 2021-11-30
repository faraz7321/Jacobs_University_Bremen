/*
CH-230-A
a13_p1.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
    string filename, line;
    ifstream fin;  //input file
    ofstream fout; //output file

    cout << "Enter filename: ";
    getline(cin, filename, '.');

    fin.open(filename + ".txt");

    if (!fin.is_open())
    {
        cout << "error opening file" << endl;
        return 0;
    }

    fout.open(filename + "_copy" + ".txt");
    if (!fout.is_open())
    {
        cout << "error opening file" << endl;
        return 0;
    }

    //copying data from input.txt to input_copy.txt
    cout << "copying data!" << endl;
    while (!fin.eof())
    {
        getline(fin, line);
        fout << line << endl;
    }
    cout << "data copied successfully!" << endl;

    //closing files
    fin.close();
    fout.close();

    return 0;
}