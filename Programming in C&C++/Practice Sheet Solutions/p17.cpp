#include <iostream>
#include <string.h>

using namespace std;

class Book
{
    private :
        char* title;
        int pages;
    public :
        Book(const Book&);
        Book(const char* t, int p) {
            title = new char[30];
            for (int i=0; t[i]!='\0'; i++)
                    title[i] = t[i];
            pages = p;}
        Book();
        //...
        //setter and getter methods omitted

        //extra : print method
        void print() {cout << "Book is " << title << " and has " << pages << endl;}
};

//copy constructor
Book :: Book(const Book& b)
{
    title = new char[30];
   for (int i=0; b.title[i]!='\0'; i++)
       title[i] = b.title[i];
    //strcpy(title, b.title);
    pages = b.pages;
}

int main()
{
    /* b) If we would have a default copy constructor, considering
    we need to dynamically allocate memory for the title, when we would
    use it we would get 2 objects which point to the same memory.
    As such, changes would be reflected in both instances. Furthermore,
    when we would use delete in one object, we would have memory leaks for
    the other one. By implementing our own copy constructor, we get rid
    of this memory problem. */

    const char *ptr;
    ptr = new char[30];
    ptr = "THRONE OF GLASS";
    Book b(ptr, 300);

    Book c(b);

    b.print();
    c.print();

    return 0;
}
