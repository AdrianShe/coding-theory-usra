#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "fib.h"
#include "sequences_linear_one_dim.h"
#include <algorithm>    // std::sort
#include <bitset>
using namespace std;
using namespace Eigen;


// generate linear one dimensional sequences of length
std::vector<long> generate_linear_one_dim_sequences(int length){
    return generate_linear_one_dim_sequences_helper(length, generate_fib_array(length+2));
}

// use fibonnaci table to generate linear one dimensional sequences of length
std::vector<long> generate_linear_one_dim_sequences_helper(int length, std::vector<int> array) {
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
/*
int main(int argc, char* argv[]) {
    int length = atoi(argv[1]);   
    cout << " generating sequences of length " << length << endl;
    for (int i = 0; i < generate_linear_one_dim_sequences(length).size(); i++){
     cout << std::bitset<16>(generate_linear_one_dim_sequences(length)[i]) << endl;
    }

  cout << " sizes " << endl;
   for (int i = 1; i <= length; i++){
     cout << generate_linear_one_dim_sequences(i).size() << endl;
   }
}
*/
