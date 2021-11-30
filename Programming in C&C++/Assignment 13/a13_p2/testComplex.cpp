/*
CH-230-A
testcomplex.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <fstream>
#include <sstream>
#include <vector>
#include "Complex.h"

// filehandeling functions
void loadData(string fileName, Complex &);
void saveData(Complex c[]);

int main()
{
    /* initializing instances by
     loading data from files */
    Complex c1;
    Complex c2;
    loadData("in1.txt", c1);
    loadData("in2.txt", c2);

    Complex op_list[3];   // a list which saves operations
    op_list[0] = c1 + c2; // addition
    op_list[1] = c1 - c2; // subtraction
    op_list[2] = c1 * c2; // multiplication

    // console output
    cout << "Sum = " << op_list[0] << endl;
    cout << "Difference = " << op_list[1] << endl;
    cout << "Product = " << op_list[2] << endl;
    saveData(op_list); // saving data to file

    return 0;
}
/**
 * @brief load data from file
 *
 * @param fileName
 * @return Complex&
 */
void loadData(string fileName, Complex &c)
{
    /*
     * it is assumed that data in file is
     * seperated with semicolon as delimeter
     * x;y
     * where x is real part
     * and y is imaginary
     */
    string line;
    ifstream fin; // input files
    fin.open(fileName);
    if (!fin.is_open())
    {
        cout << "error opening file" << endl;
        exit(0);
    }
    getline(fin, line);
    stringstream ss(line);
    vector<string> v;
    // using semicolon as delimeter
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ';');
        v.push_back(substr);
    }
    // converting from string to int
    c.setReal(stoi(v[0]));
    c.setImag(stoi(v[1]));
    fin.close();
}
/**
 * @brief saves data to output.txt
 *
 * @param c
 */
void saveData(Complex c[])
{
    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open())
    {
        cout << "error opening file" << endl;
        exit(0);
    }
    fout << "Sum= " << c[0] << endl
         << "Difference= " << c[1] << endl
         << "Product= " << c[2] << endl;
}