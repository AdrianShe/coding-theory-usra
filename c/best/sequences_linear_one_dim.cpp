#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "fib.h"
#include <algorithm>    // std::sort
#include <bitset>
using namespace std;
using namespace Eigen;

// use fibonnaci table to generate linear one dimensional sequences of length
std::vector<long> generate_sequences_helper(int length, std::vector<int> array) {
    // Create the array of fibonnaci numbers
//    int array[length+2];
   // Initialize the array
    std::vector<long> init(array[length+1]);
    init[0]=0;   
    init[1]=1;
    int pos;
    int end; 
    // Now iterate
    for (int i = 2; i <= length; i++) {
        pos = array[i];
        end = array[i-1];
        for (int j = 0; j <end; j++) {
            init[pos] = init[j] | (1 << i - 1);
            pos++;  
           // init.push_back(init[j] | (1 << i - 1)); 
        }            
    }
    return init;
}

// generate linear one dimensional sequences of length
std::vector<long> generate_linear_one_dim_sequences(int length){
    return generate_sequences_helper(length, generate_fib_array(length+2));
}


int main(int argc, char* argv[]) {
    int length = atoi(argv[1]);   
    cout << " generating new sequences " << endl;
    clock_t t_new = clock(); 
    for (int i = 0; i < length; i++){
     generate_linear_one_dim_sequences(i);
    }
    t_new = clock() - t_new;
    cout << " time " << t_new << endl;;

  cout << " sizes " << endl;
   for (int i = 1; i <= length; i++){
     cout << generate_linear_one_dim_sequences(i).size() << endl;
   }
}
