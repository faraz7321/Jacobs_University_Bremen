/*
CH-231-1
problem6.cpp
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
using namespace std;
bool loadData(map<string, string> &mymap, string filename);
int main()
{
    string search; // store input from user

    // map
    map<string, string> mymap;
    // iter for map
    std::map<string, string>::iterator it;
    loadData(mymap, "data.txt"); // loading data to map

    // simulate querying my collection
    do
    {
        cout << "Enter full name: ";
        getline(cin, search);
        it = mymap.find(search);
        if (it != mymap.end())
        {
            cout << it->first
                 << " born on " << it->second << '\n';
        }
        else
        {
            cout << "Name not found!";
        }
        cout << endl;
    } while (search != "exit");
    return 0;
}

/**
 * @brief load data from .txt to map
 *
 * @param mymap
 * @return true
 * @return false
 */
bool loadData(map<string, string> &mymap, string filename)
{
    string name, dob;
    string line;
    stringstream ss;
    ifstream myfile(filename);
    if (!myfile.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        while (!myfile.eof())
        {
            getline(myfile, line);
            name = line;
            getline(myfile, line);
            dob = line;
            mymap.insert({name, dob});
        }
        myfile.close();
        return true;
    }
}