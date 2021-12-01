/*
CH-230-A
a13_p3.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int main()
{
    int n;
    string *fileNames, line;
    ifstream *fin;
    ofstream fout;

    cout << "Enter value: ";
    cin >> n;

    fileNames = new string[n]; // n files
    fin = new ifstream[n];     // n pointers for n files

    // reading n file names;
    cout << "Enter file names:\n\n";
    for (int i = 0; i < n; i++)
    {
        cout << "File " << i + 1 << ": ";
        cin >> fileNames[i];
    }

    fout.open("concatn.txt");
    if (!fout.is_open())
    {
        cout << "error opening concatn.txt file" << endl;
        exit(0);
    }

    for (int i = 0; i < n; i++)
    {
        fin[i].open(fileNames[i]);
        if (!fin[i].is_open())
        {
            cout << "error opening input file" << i << endl;
            exit(0);
        }
        // writing to output file
        while (!fin[i].eof())
        {
            getline(fin[i], line);
            fout << line << "\n";
        }
        fin[i].close();
    }
    cout << "Successfully wrote to file!" << endl;
    fout.close();
    return 0;
}
