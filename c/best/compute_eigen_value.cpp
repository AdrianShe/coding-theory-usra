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
#include "sequences_linear_two_dim.h"
#include "sequences_ring_one_dim.h"
#include "sequences_ring_two_dim.h"
#include "compute_eigen_value.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>

using namespace std;
using namespace Eigen;

double compute_eigen_ring_lower(int length){
    return compute_eigen_lower_helper(length, generate_ring_one_dim_sequences(length), generate_ring_two_dim_sequences(length));
}
double compute_eigen_linear_lower(int length){
    return compute_eigen_lower_helper(length, generate_linear_one_dim_sequences(length), generate_linear_two_dim_sequences(length));
}

double compute_eigen_ring_upper(int length){
    return compute_eigen_upper_helper(length, generate_ring_one_dim_sequences(length), generate_ring_two_dim_sequences(length));
}
double compute_eigen_linear_upper(int length){
    return compute_eigen_upper_helper(length, generate_linear_one_dim_sequences(length), generate_linear_two_dim_sequences(length));
}


double compute_eigen_lower_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs){    
    int size = table.size();
    Eigen::VectorXd vec(size);
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::map<int, int> m;
    for (int i = 0; i < size; i++){
        m[table[i]]=i;
    } 
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < seqs.size(); i++){
            std::pair<long,long> sample = seqs[i];
            new_vec(m[sample.first])+=vec(m[sample.second]);
         }
        eigen_old = eigen_guess;
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
    return eigen_guess;
}

double compute_eigen_upper_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs){
    int size = table.size();
    Eigen::VectorXd vec(size);
    double sample;
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::map<int, int> m;
   for (int i = 0; i < size; i++){
        m[table[i]]=i;
   } 
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < seqs.size(); i++){
            std::pair<long,long> sample = seqs[i];
            new_vec(m[sample.first])+=vec(m[sample.second]);
         }
        eigen_old = eigen_guess;
        eigen_guess = 0;  
        for (int i = 0; i < size; i++){
            sample = new_vec(i)/vec(i);
            if (sample > eigen_guess) eigen_guess = sample;
        }
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
   return eigen_guess;
}
/*
int main(int argc, char* argv[]) {
    int input= atoi(argv[1]);
    cout << " LINEAR " << endl;
    cout <<"lower " << setprecision(16) <<   compute_eigen_linear_lower(input) << endl;
    cout <<"upper " <<  compute_eigen_linear_upper(input) << endl;
    cout << " RING " << endl;
    cout <<"lower " <<  compute_eigen_ring_lower(input) << endl;
    cout <<"upper " <<  compute_eigen_ring_upper(input) << endl;
     
 
}

*/
