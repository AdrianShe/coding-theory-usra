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
#include "sequences_ring_one_dim.h"
#include "compute_eigen_value_one_dim.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>

using namespace std;
using namespace Eigen;

double compute_eigen_ring_one_dim_lower(int length){
    return compute_eigen_lower_one_dim_helper(length, generate_ring_one_dim_sequences(length));
}
double compute_eigen_linear_one_dim_lower(int length){
    return compute_eigen_lower_one_dim_helper(length, generate_linear_one_dim_sequences(length));
}
double compute_eigen_ring_one_dim_upper(int length){
    return compute_eigen_upper_one_dim_helper(length, generate_ring_one_dim_sequences(length));
}
double compute_eigen_linear_one_dim_upper(int length){
    return compute_eigen_upper_one_dim_helper(length, generate_linear_one_dim_sequences(length));
}

double compute_eigen_lower_one_dim_helper(int length, std::vector<long> seqs){    
    int size = seqs.size();
//    cout << size << endl;
//    cout << endl;
    Eigen::VectorXd vec(size);
    vec.fill(1);
//    cout << vec << endl;
    Eigen::VectorXd new_vec(size);
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
//        cout << vec << endl;
        for (int i = 0; i < size; i++){
            long sample = seqs[i];
            for (int j = i; j < size; j++){
                long comp = seqs[j];
                if (!(sample & comp)){
                    new_vec(i)+=vec(j);
                    if( i != j) new_vec(j)+=vec(i);
                }
            }
         }
//        cout << endl;
//        cout << new_vec << endl;
//        cout << endl;
        eigen_old = eigen_guess;
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
    return eigen_guess;
}

double compute_eigen_upper_one_dim_helper(int length, std::vector<long> seqs){
    int size = seqs.size();
    Eigen::VectorXd vec(size);
    double candidate;
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < size; i++){
            long sample = seqs[i];
            for (int j = i; j< size; j++){
                long comp = seqs[j];
                if (!(sample & comp)){
                    new_vec(i)+=vec(j);
                    if (i!=j) new_vec(j)+=vec(i);
                }
            }
         }
        eigen_old = eigen_guess;
        eigen_guess = 0;  
        for (int i = 0; i < size; i++){
            candidate = new_vec(i)/vec(i);
            if (candidate > eigen_guess) eigen_guess = candidate;
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
    cout <<"lower " << setprecision(16) <<   compute_eigen_linear_one_dim_lower(input) << endl;
    cout <<"upper " <<  compute_eigen_linear_one_dim_upper(input) << endl;
    cout << " RING " << endl;
    cout <<"lower " <<  compute_eigen_ring_one_dim_lower(input) << endl;
    cout <<"upper " <<  compute_eigen_ring_one_dim_upper(input) << endl;
     
 
}
*/

