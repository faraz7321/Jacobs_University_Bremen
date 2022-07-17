#include <iostream>

using namespace std;

int main() {
	int* ptr;

	static_assert(sizeof(ptr) == 8, "This code only runs on 64-bit systems");
	//static_assert(sizeof(ptr) == 4, "Oh, you are not using a 32-bit system...");
	/*
    ....
    */
}


