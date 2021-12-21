#include <iostream>

using namespace std;

int main()
{
    int x, y;

    cin >> x >> y;

    try {
        if (y == 0)
            throw logic_error("Division by zero.");
        cout << x/y << endl;
    }
    catch (logic_error &e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
