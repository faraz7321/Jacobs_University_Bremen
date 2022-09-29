#include <iostream>
using namespace std;

union myUnion {
    char a;
     double points;
    int age;
   
};

int main() {
    myUnion obj;
    obj.age = 12;
    obj.a = 'b';
    obj.points = 5.563;
    cout << "age : " << obj.age << endl;
    cout << "a : " << obj.a << endl;
    cout << "points : " << obj.points << endl;

}
