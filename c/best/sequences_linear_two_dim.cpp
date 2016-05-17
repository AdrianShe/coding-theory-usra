#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "fib.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>

using namespace std;
using namespace Eigen;

std::vector<std::pair<long,long> > generate_linear_two_dim_sequences(int length) {
// Create the arrays of sequences
    std::vector<std::pair<long,long> > ret;
    std::vector< vector<std::pair<long,long> > > end_in_zeros;
    std::vector< vector<std::pair<long,long> > > end_in_top;
    std::vector< vector<std::pair<long,long> > > end_in_bottom;
  
//  Initialize the end_in_zero array
    std::pair <long, long > zeros (0,0);
    std::vector<pair<long,long> > init_z;
    init_z.push_back(zeros);   
    end_in_zeros.push_back(init_z);
    
//  Initialize the end_in_top array
    std::pair <long, long > top (1,0);
    std::vector<std::pair<long,long> > init_t;
    init_t.push_back(top);   
    end_in_top.push_back(init_t);
    
//  Initialize the end_in_top array
    std::pair <long, long > bottom (0,1);
    std::vector<std::pair<long,long> > init_b;
    init_b.push_back(bottom);   
    end_in_bottom.push_back(init_b);    

//  Now iterate
    for (int i = 1; i < length; i++) {
        std::vector<pair<long,long> > zero_seqs;
        std::vector<pair<long,long> > top_seqs;
        std::vector<pair<long,long> > bottom_seqs;
     
//      look at the end_in_zero array
        for (int j = 0; j < end_in_zeros[i-1].size(); j++){
            std::pair <long, long > sample = end_in_zeros[i-1][j];
            long top = sample.first;
            long bottom = sample.second;

//          add to end_in_zeros
            long new_top_z = top << 1;
            long new_bottom_z = bottom << 1;
            std::pair <long, long > new_seq_z (new_top_z, new_bottom_z);
            zero_seqs.push_back(new_seq_z); 

//          add to end_in_top
            long new_top_t = (top << 1) | 1;
            long new_bottom_t = bottom << 1;
            std::pair <long, long > new_seq_t (new_top_t, new_bottom_t);
            top_seqs.push_back(new_seq_t); 
    
//          add to end_in_bottom
            long new_top_b = top << 1;
            long new_bottom_b = (bottom << 1) | 1;
            std::pair <long, long > new_seq_b (new_top_b, new_bottom_b);
            bottom_seqs.push_back(new_seq_b);  
        }

//      look at the end_in_top array
        for (int k = 0; k < end_in_top[i-1].size(); k++){
            std::pair <long, long > sample = end_in_top[i-1][k];
            long top = sample.first;
            long bottom = sample.second;

//          add to end_in_zeros
            long new_top_z = top << 1;
            long new_bottom_z = bottom << 1;
            std::pair <long, long > new_seq_z (new_top_z, new_bottom_z);
            zero_seqs.push_back(new_seq_z); 

 //         add to end_in_bottom
            long new_top_b = top << 1;
            long new_bottom_b = (bottom << 1) | 1;
            std::pair <long, long > new_seq_b (new_top_b, new_bottom_b);
            bottom_seqs.push_back(new_seq_b);        
        }

//      look at the end_in_bottom array
        for (int l = 0; l < end_in_bottom[i-1].size(); l++){
            std::pair <long, long > sample = end_in_bottom[i-1][l];
            long top = sample.first;
            long bottom = sample.second;
            
//          add to end_in_zeros
            long new_top_z = top << 1;
            long new_bottom_z = bottom << 1;
            std::pair <long, long > new_seq_z (new_top_z, new_bottom_z);
            zero_seqs.push_back(new_seq_z); 

//          add to end_in_top
            long new_top_t = (top << 1) | 1;
            long new_bottom_t = bottom << 1;
            std::pair <long, long > new_seq_t (new_top_t, new_bottom_t);
            top_seqs.push_back(new_seq_t); 
        }
        end_in_zeros.push_back(zero_seqs);
        end_in_top.push_back(top_seqs);
        end_in_bottom.push_back(bottom_seqs);
    }
//  preallocate memory
    ret.reserve( end_in_zeros[length-1].size() + end_in_top[length-1].size() + end_in_bottom[length-1].size());
    ret.insert( ret.end(), end_in_zeros[length-1].begin(), end_in_zeros[length-1].end() );
    ret.insert( ret.end(), end_in_top[length-1].begin(), end_in_top[length-1].end() );
    ret.insert( ret.end(), end_in_bottom[length-1].begin(), end_in_bottom[length-1].end() );
    return ret;
}
/*
int main(int argc, char* argv[]) {
    int input= atoi(argv[1]);
    std::vector<std::pair<long,long> > ret = generate_linear_two_dim_sequences(input);
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
