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
#include <vector>
using namespace std;
int main()
{
    string input, line, fileName, fileExt;
    ifstream fin;  //input file
    ofstream fout; //output file

    cout << "Enter filename: ";
    getline(cin, input);

    //splitting string into file name and its extention
    vector<string> v;
    stringstream ss(input);

    while (ss.good())
    {
        string substr;
        getline(ss, substr, '.');
        v.push_back(substr);
    }
    fileName = v[0];
    fileExt = "." + v[1];

    fin.open(input);

    if (!fin.is_open())
    {
        cout << "error opening file" << endl;
        return 0;
    }

    fout.open(fileName + "_copy" + fileExt);
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