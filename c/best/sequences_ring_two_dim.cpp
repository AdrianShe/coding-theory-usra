#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "fib.h"
#include "sequences_linear_two_dim.h"
#include "sequences_ring_two_dim.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>


using namespace std;
using namespace Eigen;

std::vector<std::pair<long,long> > generate_ring_two_dim_sequences(int length){
    return keep_two_dim_rings(generate_linear_two_dim_sequences(length), length);
}

bool is_two_dim_ring(std::pair<long,long> sample, int length){
    long top = sample.first;
    long bottom = sample.second;
    if (top % 2 == 1 && (top >> (length-1)) % 2 == 1)
        return false;
    if (bottom % 2 == 1 && (bottom >> (length-1)) % 2 == 1)
        return false;
    return true;
}

std::vector<std::pair<long,long> > keep_two_dim_rings(std::vector<std::pair<long,long> > seqs, int length){
    std::vector<std::pair<long,long> > ret;
    for (int i = 0; i < seqs.size(); i++){
        if (is_two_dim_ring(seqs[i], length)) ret.push_back(seqs[i]);
    }
    return ret;
}
/*
int main(int argc, char* argv[]) {
    int input = atoi(argv[1]);
    std::vector<std::pair<long,long> > ret = generate_ring_two_dim_sequences(input);
    cout << "sequences !!" << endl;
    for (int i = 0; i < ret.size(); i++){
        std::pair<long,long> sample = ret[i];
        long top = sample.first;
        long bottom = sample.second;
        cout << std::bitset<16>(top) << endl;
        cout << std::bitset<16>(bottom) << endl;
        cout << endl;
   }

}
*/
