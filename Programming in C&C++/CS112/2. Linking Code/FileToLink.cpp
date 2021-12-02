#include <iostream>

int factorial(int n) {
    if (n==0 || n == 1)
        return 1;
    else
        return n*factorial(n-1);
}

int sum(int n) {
    if(n == 0) {
        return 0;
    } else if(n < 0) {
        return sum(n+1) + n;
    } else {
        return sum(n-1) + n;
    }
}
