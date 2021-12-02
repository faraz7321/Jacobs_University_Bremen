#include <iostream>

using namespace std;

class SortClass 
{
    private:
        int *list;
        int listsize;    
    
    public:
        void getInput() {
            cout << "Enter the size of the list : ";
            cin >> listsize;

            list = new int[listsize];
            
            for(int i = 0; i < listsize; i++) {
                cout << "Enter a number : ";
                cin >> list[i];
            }
            cout << endl;
        }
        
        void display() {
            for(int i = 0; i < listsize; i++)
                cout << list[i] << " ";
            cout << endl;
        }

        void sortArray() {
            for(int i = 0; i < listsize - 1; i++) {
                for(int j = i + 1; j < listsize; j++) {
                    if(list[i] > list[j]) {
                        int temp = list[i];
                        list[i] = list[j];
                        list[j] = temp; 
                    }
                }
            }
        }
};

int main() {
    SortClass firstObj;
    firstObj.getInput();
    cout << "List as entered before sorting : " << endl;
    
    firstObj.display();
    firstObj.sortArray();
    cout << "List after sorting : " << endl;
    
    firstObj.display();
}