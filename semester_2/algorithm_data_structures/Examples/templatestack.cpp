#include <cassert>
#include <iostream>

using namespace std;

/* 
This is a generic stack. Its type T is generic and its initial 
size defaults to 10.
*/
template<class T, int initialsize = 10>
class Stack 
{
	T *ptr;			// data will be stored in an array
	int size;		// number of elements in the array
	int where;  	// last non-free position
	void extend();  // used to expand the vector when it is full
public:
	Stack();
	~Stack();
	void push(const T&);	// inserts an element
	const T& pop();			// returns and extracts an element
};

template<class T, int initialsize>
Stack<T, initialsize>::Stack() 
{
	ptr = new T[initialsize];	// creates a vector of the given size
	size = initialsize;
	where = -1;					// no elements up to now
}

template<class T, int initialsize>
Stack<T, initialsize>::~Stack()
{
	delete[] ptr;			// deallocate memory
} 

template<class T, int initialsize>
void Stack<T, initialsize>::push(const T& topush)
{
	if (where + 1 == size)	// no room?  
		extend();			// expand the vector
	where++;				// and insert the element 
	ptr[where] = topush;
}

template<class T, int initialsize>
void Stack<T, initialsize>::extend()
{
	T *newptr = new T[2 * size];	// creates a new vector with double size
	for (int i = 0; i < size; i++)	// copy the old elements
		newptr[i] = ptr[i];
	delete[] ptr;	// release old memory
	ptr = newptr;	// adjust pointers
	size *= 2;		// store the new size
}

template<class T,int initialsize>
const T& Stack<T,initialsize>::pop()
{
	assert(where >= 0);   // non pops if no elements are present
	return ptr[where--];  // return the element and update the free position
}


int main(int argc, char** argv)
{
	Stack<int> intstack;  			// stack with the default size
	Stack<float, 1000> floatstack;  // stack with specified size
	
	int i;

	for (i = 0; i < 20; i++)
		intstack.push(i);

	for (i = 0; i < 20; i++)
		cout << intstack.pop() << endl;

	intstack.pop(); // let it fail
}
