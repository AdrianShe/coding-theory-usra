#include <iostream>
#include <cstdlib>
#include "fib.h"
#include <vector>
using namespace std;

// Function returns the nth Fibonacci number F_n, using
// the convention that F_1 = 1 and F_2 = 1
int fib(int n) {
    if (n == 1) {
       return 1;
    }
    if (n == 2) {
       return 1;
    }
    else {
      int array[n];
      array[0] = 1;
      array[1] = 1;
      for ( int i=2; i <= n - 1; i++ ) {
         array[i] = array[i-1] + array[i-2];
      }
      return array[n - 1];
    }    
}

/*
  int main( int argc, char* argv[]) {
    for (int i = 1; i < atoi(argv[1]); i++ ) {
       cout << fib(i) << " ";
   }
    cout << endl;
    for (int i = 1; i < atoi(argv[1]); i++ ) {
       cout << fib_new(i) << " ";
   }

 }
*/

