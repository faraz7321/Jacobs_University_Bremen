#include <iostream>

using namespace std;

class worker
{
private :
    int nr;
    std::string name;
public :
    worker();
    worker(int, const std::string&);
    friend ostream& operator<<(ostream&, const worker&);
};

worker :: worker (int a,const std::string& n)
{
    name = n;
    nr = a;
}

ostream& operator<<(ostream& out, const worker& a)
{
    out << "Number of worker is " << a.nr << " and name is " << a.name << endl;
}
int main()
{
    worker a(234, "John McEnroe");
    worker b(324, "Jack Nicholson");
    cout << a << b;
    return 0;
}
