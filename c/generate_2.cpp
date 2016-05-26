#include <vector>
#include <Eigen/Dense>
#include "generate.h"
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

std::vector<std::pair<long,long> > generate_2_sequences(int length) {
    // Create the arrays of sequences
   std::vector<std::pair<long,long> > ret;
   std::vector< vector<std::pair<long,long> > > end_in_zeros;
   std::vector< vector<std::pair<long,long> > > end_in_top;
   std::vector< vector<std::pair<long,long> > > end_in_bottom;
  
//   cout << " finished creating " << endl;
    // Initialize the end_in_zero array
    std::pair <long, long > zeros (0,0);
    std::vector<pair<long,long> > init_z;
    init_z.push_back(zeros);   
    end_in_zeros.push_back(init_z);
    
    // Initialize the end_in_top array
    std::pair <long, long > top (1,0);
    std::vector<std::pair<long,long> > init_t;
    init_t.push_back(top);   
    end_in_top.push_back(init_t);
    
    // Initialize the end_in_top array
    std::pair <long, long > bottom (0,1);
    std::vector<std::pair<long,long> > init_b;
    init_b.push_back(bottom);   
    end_in_bottom.push_back(init_b);    

 //   cout << " finished initializing " << endl;

    // Now iterate
    for (int i = 1; i < length; i++) {
     std::vector<pair<long,long> > zero_seqs;
     std::vector<pair<long,long> > top_seqs;
     std::vector<pair<long,long> > bottom_seqs;
 
/*     cout << " looking at length " << i << endl;
    cout << " first element in  end in zeros is " << end_in_zeros[i-1][0].first << endl;
     cout << " secnd elment end in zeros is " << end_in_zeros[i-1][0].second << endl;
     cout << " first element in  end in top is " << end_in_top[i-1][0].first << endl;
     cout << " second  end in top is " << end_in_top[i-1][0].second << endl;    
 */

    // look at the end_in_zero array
        for (int j = 0; j < end_in_zeros[i-1].size(); j++){
       //   cout << " looking at zeros of length " << i -1 << " at " << j << endl;  
            std::pair <long, long > sample = end_in_zeros[i-1][j];
            long top = sample.first;
            long bottom = sample.second;
  //          cout << top  << bottom << endl;
            // add to end_in_zeros
            long new_top_z = top << 1;
            long new_bottom_z = bottom << 1;
            std::pair <long, long > new_seq_z (new_top_z, new_bottom_z);
            zero_seqs.push_back(new_seq_z); 
   //         cout << new_top_z  << new_bottom_z << endl;
            // add to end_in_top
            long new_top_t = (top << 1) | 1;
            long new_bottom_t = bottom << 1;
            std::pair <long, long > new_seq_t (new_top_t, new_bottom_t);
            top_seqs.push_back(new_seq_t); 
    

            // add to end_in_bottom
            long new_top_b = top << 1;
            long new_bottom_b = (bottom << 1) | 1;
            std::pair <long, long > new_seq_b (new_top_b, new_bottom_b);
            bottom_seqs.push_back(new_seq_b);
  //      cout << " finished j =  " << j << endl;        
        }

           // look at the end_in_top array
        for (int k = 0; k < end_in_top[i-1].size(); k++){
    //     cout << " looking at top of length " << i -1 << " at " << k << endl;  
           
            std::pair <long, long > sample = end_in_top[i-1][k];
            long top = sample.first;
            long bottom = sample.second;
            
            // add to end_in_zeros
            long new_top_z = top << 1;
            long new_bottom_z = bottom << 1;
            std::pair <long, long > new_seq_z (new_top_z, new_bottom_z);
            zero_seqs.push_back(new_seq_z); 

            // add to end_in_bottom
            long new_top_b = top << 1;
            long new_bottom_b = (bottom << 1) | 1;
            std::pair <long, long > new_seq_b (new_top_b, new_bottom_b);
            bottom_seqs.push_back(new_seq_b);        
        }

         // look at the end_in_bottom array
        for (int l = 0; l < end_in_bottom[i-1].size(); l++){
      //       cout << " looking at bottom of length " << i -1 << " at " << l << endl;  
           
            std::pair <long, long > sample = end_in_bottom[i-1][l];
            long top = sample.first;
            long bottom = sample.second;
            
            // add to end_in_zeros
            long new_top_z = top << 1;
            long new_bottom_z = bottom << 1;
            std::pair <long, long > new_seq_z (new_top_z, new_bottom_z);
            zero_seqs.push_back(new_seq_z); 

            // add to end_in_top
            long new_top_t = (top << 1) | 1;
            long new_bottom_t = bottom << 1;
            std::pair <long, long > new_seq_t (new_top_t, new_bottom_t);
            top_seqs.push_back(new_seq_t); 
        }
    end_in_zeros.push_back(zero_seqs);
    end_in_top.push_back(top_seqs);
    end_in_bottom.push_back(bottom_seqs);

    }
    ret.reserve( end_in_zeros[length-1].size() + end_in_top[length-1].size() + end_in_bottom[length-1].size()); // preallocate memory
    ret.insert( ret.end(), end_in_zeros[length-1].begin(), end_in_zeros[length-1].end() );
    ret.insert( ret.end(), end_in_top[length-1].begin(), end_in_top[length-1].end() );
ret.insert( ret.end(), end_in_bottom[length-1].begin(), end_in_bottom[length-1].end() );
    return ret;
 }

bool is_ring(std::pair<long,long> sample, int length){
    long top = sample.first;
    long bottom = sample.second;
    if (top % 2 == 1 && (top >> (length-1)) % 2 == 1)
        return false;
    if (bottom % 2 == 1 && (bottom >> (length-1)) % 2 == 1)
        return false;
    return true;
}

std::vector<std::pair<long,long> > keep_rings(std::vector<std::pair<long,long> > seqs, int length){
    std::vector<std::pair<long,long> > ret;
    for (int i = 0; i < seqs.size(); i++){
        if (is_ring(seqs[i], length)) ret.push_back(seqs[i]);
    }
    return ret;
}

std::vector<std::pair<long,long> > generate_rings_2(int length){
    return keep_rings(generate_2_sequences(length), length);
}

Eigen::MatrixXd generate_matrix_2(int length){
// compute size
  int size = fib(length + 2);
  // create matrix
  Eigen::MatrixXd transfer(size,size);
  transfer.fill(0);
  // prepare index map
  std::vector<long> table = generate_new_sequences(length);
  std::map<int, int> m;
//   cout << " table size " << table.size() << endl;
//  cout << "matrix size " << size << endl;
  for (int i = 0; i < table.size(); i++){
      m[table[i]]=i;
//      cout << " key " << table[i]  << " val " << i << endl;
  } 
//  cout << " generating matrix" << endl;
//generate matrix
  std::vector<std::pair<long,long> > ret =  generate_2_sequences(length);
// cout << "ret.size " << ret.size() << endl; 
  for (int i = 0; i < ret.size(); i++){
 //     cout << " accessing " << i << endl;
      std::pair<long,long> sample = ret[i];
 //     cout << " putting " << sample.first << " " << sample.second << endl;
 //     cout << " in " << m[sample.first] << " " << m[sample.second] << endl;
      transfer(m[sample.first], m[sample.second]) = 1;
 //     cout << transfer << endl;
 //     cout << " insertion complete " << endl;
  }
//  cout << " generated matrix " << endl;
  return transfer;
} 

double generate_eigen(int length){
    int size = fib(length + 2);
    Eigen::VectorXd vec(size);
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::vector<long> table = generate_new_sequences(length);
    std::map<int, int> m;
//   cout << " table size " << table.size() << endl;
//  cout << "vector size " << size << endl;
    for (int i = 0; i < table.size(); i++){
        m[table[i]]=i;
//      cout << " key " << table[i]  << " val " << i << endl;
    } 
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    std::vector<std::pair<long,long> > ret =  generate_2_sequences(length);
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < ret.size(); i++){
            std::pair<long,long> sample = ret[i];
            new_vec(m[sample.first])+=vec(m[sample.second]);
         }
        eigen_old = eigen_guess;
//        cout << " old vec " << vec << endl;
//        cout << " new vec " << new_vec << endl;
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
//    cout << " answer " << setprecision(16) << eigen_guess << endl;
    return eigen_guess;
}
double generate_eigen_ring(int length){
    int size = fib(length + 2);
    Eigen::VectorXd vec(size);
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::vector<long> table = generate_new_sequences(length);
    std::map<int, int> m;
//   cout << " table size " << table.size() << endl;
//  cout << "vector size " << size << endl;
    for (int i = 0; i < table.size(); i++){
        m[table[i]]=i;
//      cout << " key " << table[i]  << " val " << i << endl;
    } 
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    std::vector<std::pair<long,long> > ret =  generate_2_sequences(length);
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < ret.size(); i++){
            std::pair<long,long> sample = ret[i];
            new_vec(m[sample.first])+=vec(m[sample.second]);
         }
        eigen_old = eigen_guess;
//        cout << " old vec " << vec << endl;
//        cout << " new vec " << new_vec << endl;
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
//    cout << " answer " << setprecision(16) << eigen_guess << endl;
    return eigen_guess;
}

double generate_eigen_upper(int length){
    int size = fib(length + 2);
    Eigen::VectorXd vec(size);
    double sample;
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::vector<long> table = generate_new_sequences(length);
    std::map<int, int> m;
//   cout << " table size " << table.size() << endl;
//  cout << "vector size " << size << endl;
    for (int i = 0; i < table.size(); i++){
        m[table[i]]=i;
//      cout << " key " << table[i]  << " val " << i << endl;
    } 
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    std::vector<std::pair<long,long> > ret =  generate_2_sequences(length);
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < ret.size(); i++){
            std::pair<long,long> sample = ret[i];
            new_vec(m[sample.first])+=vec(m[sample.second]);
         }
        eigen_old = eigen_guess;
//        cout << " old vec " << vec << endl;
//        cout << " new vec " << new_vec << endl;
        eigen_guess = 0;  
        for (int i = 0; i < size; i++){
            sample = new_vec(i)/vec(i);
            if (sample > eigen_guess) eigen_guess = sample;
        }
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
//    cout << " upper " << setprecision(16) << eigen_guess << endl;
    return eigen_guess;
}

int main(int argc, char* argv[]) {
    int input= atoi(argv[1]);
    std::vector<std::pair<long,long> > ret = generate_rings_2(input);
  cout << "sequences !!" << endl;
     for (int i = 0; i < ret.size(); i++){
      std::pair<long,long> sample = ret[i];
      long top = sample.first;
      long bottom = sample.second;
      cout << std::bitset<16>(top) << endl;
      cout << std::bitset<16>(bottom) << endl;
      cout << endl;
   }

        
    /*
    cout << " sequences !!" << endl;
    for (int i = 0; i < ret.size() ; i++){
        cout<< ret[i].first << " " << ret[i].second << endl;    
    }
    */
    cout << " sizes!! " << endl;
    for (int i = 1; i <= input ; i ++){
        cout << generate_rings_2(i).size() << endl;
    }


//    cout << generate_matrix_2(input) << endl;
 }

