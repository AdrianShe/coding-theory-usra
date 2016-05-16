#include <iostream>
#include <cstdlib>
#include "fib.h"
#include <vector>
using namespace std;

// Function returns the nth Fibonacci number F_n, using
// the convention that F_1 = 1 and F_2 = 1
int fib(int n) {
    return generate_fib_array(n)[n-1];
}

 // calculates first n fibonnaci numbers where F_n = array[n-1] !
std::vector<int> generate_fib_array(int n){
    std::vector<int> array(n);
    if (n >= 1) array[0] = 1;
    if (n >= 2) array[1] = 1;
    for (int i = 2; i < n; i++){
        array[i] = array[i-1] + array[i-2];
    }
    return array;
}
/*
int main( int argc, char* argv[]) {
    int input = atoi(argv[1]);
    cout << " calculating first " << input << " fibonnaci numbers" << endl;
    for (int i = 1; i <=input; i++ ) {
        cout << fib(i) << " ";
    }
}
*/
