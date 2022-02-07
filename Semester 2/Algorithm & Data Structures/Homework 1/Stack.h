/*
CH-231-1
Stack.h
Faraz Ahmad
fa.ahmad@jacobs-university.de
*/

/**
 * @brief Implementing stack using template
 *
 * @tparam T
 * @tparam initialsize
 */
template <class T, int initialsize = 10>
class Stack
{
    T *ptr;        // data will be stored in an array
    int size;      // number of elements in the array
    int where;     // last non-free position
    void extend(); // used to expand the vector when it is full
public:
    // constructors
    Stack();
    Stack(const Stack &);
    Stack(int);
    // deconstructor
    ~Stack();
    bool push(const T &); // inserts an element
    bool pop(T &out);     // returns and extracts an element
    T back(void);
    int getNumEntries() { return where + 1; }
};

// IMPLEMENTATION OF PUBLIC CLASS METHODS//

/**
 * @brief Construct a new Stack< T, initialsize>:: Stack object
 *
 * @tparam T
 * @tparam initialsize
 */
template <class T, int initialsize>
Stack<T, initialsize>::Stack()
{
    ptr = new T[initialsize]; // creates a vector of the given size
    size = initialsize;
    where = -1; // no elements up to now
}

/**
 * @brief Construct a new Stack< T, initialsize>:: Stack object
 * copy constructor
 *
 * @tparam T
 * @tparam initialsize
 * @param s
 */
template <class T, int initialsize>
Stack<T, initialsize>::Stack(const Stack &s)
{
    ptr = new T[initialsize]; // creates a vector of the given size
    size = s.size;
    where = s.where;

    for (int i = 0; i < where + 1; i++)
    {
        ptr = s.ptr[i];
    }
}

/**
 * @brief Construct a new Stack< T, initialsize>:: Stack object
 * constructing stack of size n
 *
 * @tparam T
 * @tparam initialsize
 * @param n
 */
template <class T, int initialsize>
Stack<T, initialsize>::Stack(int n)
{
    size = n;
}

/**
 * @brief Destroy the Stack< T, initialsize>:: Stack object
 *
 * @tparam T
 * @tparam initialsize
 */
template <class T, int initialsize>
Stack<T, initialsize>::~Stack()
{
    delete[] ptr; // deallocate memory
}

/**
 * @brief push an element into stack
 *
 * @tparam T
 * @tparam initialsize
 * @param topush
 * @return true
 * @return false
 */
template <class T, int initialsize>
bool Stack<T, initialsize>::push(const T &topush)
{
    if (where + 1 == size) // no room?
        extend();          // expand the vector
    where++;               // and insert the element
    ptr[where] = topush;
    return true;
}

/**
 * @brief extend stack limit
 *
 * @tparam T
 * @tparam initialsize
 */
template <class T, int initialsize>
void Stack<T, initialsize>::extend()
{
    T *newptr = new T[2 * size];   // creates a new vector with double size
    for (int i = 0; i < size; i++) // copy the old elements
        newptr[i] = ptr[i];
    delete[] ptr; // release old memory
    ptr = newptr; // adjust pointers
    size *= 2;    // store the new size
}

/**
 * @brief pop an element from stack
 *
 * @tparam T
 * @tparam initialsize
 * @param out
 * @return true
 * @return false
 */
template <class T, int initialsize>
bool Stack<T, initialsize>::pop(T &out)
{
    if (where >= 0)
    {
        out = ptr[where--];
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief element at the top
 *
 * @tparam T
 * @tparam initialsize
 * @return T
 */
template <class T, int initialsize>
T Stack<T, initialsize>::back(void)
{
    T top_element = ptr[where];
    return top_element;
}
