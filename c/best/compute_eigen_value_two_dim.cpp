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
#include "compute_eigen_value_two_dim.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>

using namespace std;
using namespace Eigen;

double compute_eigen_ring_two_dim_lower(int length){
    return compute_eigen_lower_two_dim_helper(length, generate_ring_one_dim_sequences(length), generate_ring_two_dim_sequences(length));
}
double compute_eigen_linear_two_dim_lower(int length){
    return compute_eigen_lower_two_dim_helper(length, generate_linear_one_dim_sequences(length), generate_linear_two_dim_sequences(length));
}

double compute_eigen_ring_two_dim_upper(int length){
    return compute_eigen_upper_two_dim_helper(length, generate_ring_one_dim_sequences(length), generate_ring_two_dim_sequences(length));
}
double compute_eigen_linear_two_dim_upper(int length){
    return compute_eigen_upper_two_dim_helper(length, generate_linear_one_dim_sequences(length), generate_linear_two_dim_sequences(length));
}


double compute_eigen_lower_two_dim_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs){    
    int size = table.size();
    Eigen::VectorXd vec(size);
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::map<int, int> m;
    for (int i = 0; i < size; i++){
        m[table[i]]=i;
    }
    std::vector<std::pair<long,long> >index;
    index.reserve(seqs.size());
    for (int i = 0; i < seqs.size(); i++){
        std::pair<long,long> sample = seqs[i];
        std::pair<long, long> mapped (m[sample.first],m[sample.second]);
        index[i] = mapped;
    } 
    double eigen_guess = -1;
    double eigen_old = 0; 
//generate "implicit matrix" eigenvalue
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
//        cout << "vec " << vec << endl;
        for (int i = 0; i < seqs.size(); i++){
            std::pair<long,long> s = index[i];
            new_vec(s.first) += vec(s.second);
        }
//        cout << " new vec " <<new_vec<< endl;
        eigen_old = eigen_guess;
        eigen_guess = vec.dot(new_vec);
        vec = new_vec;
    }
    return eigen_guess;
}

double compute_eigen_upper_two_dim_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs){
    int size = table.size();
    Eigen::VectorXd vec(size);
    double sample;
    vec.fill(1);
    Eigen::VectorXd new_vec(size);
    std::map<int, int> m;
   for (int i = 0; i < size; i++){
        m[table[i]]=i;
   } 
    std::vector<std::pair<long,long> >index;
    index.reserve(seqs.size());
    for (int i = 0; i < seqs.size(); i++){
        std::pair<long,long> sample = seqs[i];
        std::pair<long, long> mapped (m[sample.first],m[sample.second]);
        index[i] = mapped;
    } 
    double eigen_guess = -1;
    double eigen_old = 0; //generate "implicit matrix" eigenvalue
    while (abs(eigen_old-eigen_guess) > numeric_limits<double>::epsilon()){ 
        new_vec.fill(0);
        vec.normalize();
        for (int i = 0; i < seqs.size(); i++){
            std::pair<long,long> sample = index[i];
            new_vec(sample.first)+=vec(sample.second);
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
