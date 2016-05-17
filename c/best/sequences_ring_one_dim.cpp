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

std::vector<long> generate_ring_one_dim_sequences(int length) {
    std::vector<long> ret;
    switch ( length ) {
       case 3:
           ret.push_back(4);
       case 2:
           ret.push_back(2);
           ret.push_back(1);
       case 0: // Base cases are i = 0, 3 as generate_new_sequences
       case 1: // doesn't work with length < 0
          ret.push_back(0);
          break;
       default:
         std::vector<long>  end_in_zero = generate_linear_one_dim_sequences(length - 1);
         std::vector<long> end_in_one = generate_linear_one_dim_sequences(length - 3);
          for (int i = 0; i < end_in_zero.size(); i++) {
              end_in_zero[i] = (end_in_zero[i] << 1);
          }
          for (int i = 0; i < end_in_one.size(); i++) {
              end_in_one[i] = (end_in_one[i] << 2) + 1;
          }
        ret.reserve(end_in_zero.size() + end_in_one.size()); 
        ret.insert(ret.end(), end_in_zero.begin(), end_in_zero.end());
        ret.insert(ret.end(), end_in_one.begin(), end_in_one.end());
    }
   return ret;
}
/*
int main(int argc, char* argv[]) {
    int length = atoi(argv[1]);   
    cout << " sizes " << endl;
    for (int i = 1; i <= length; i++){
        cout << generate_ring_one_dim_sequences(i).size() << endl;
    }

 cout << " sequences of length "<< length << endl;
    std::vector<long> sequences = generate_ring_one_dim_sequences(length);
    for (int i = 0; i < sequences.size(); i++){
         cout << std::bitset<16>(sequences[i]) << endl;
   }

}*/
