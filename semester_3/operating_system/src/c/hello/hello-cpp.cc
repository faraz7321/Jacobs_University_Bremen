/*
 * hello-cpp.cc --
 *
 *	This file contains a C++ program using standard iostreams to
 *	print a short message. What happens if the stream is not
 *	writable?
 *
 * Exercise:
 *
 * On Linux, run the program with ltrace and strace. Explain the
 * results produced by ltrace and strace.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Hello World" << endl << flush;
    if (cout.fail()) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
