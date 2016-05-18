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
#include <algorithm>    // std::sort
#include <bitset>
using namespace std;
using namespace Eigen;

std::vector<long> generate_sequences(int length) {
    // Create the array of sequences 
   std::vector< vector<long> > temp;

    // Initialize the array
    std::vector<long> init;
    init.push_back(0);   
    temp.push_back(init);
    init.push_back(1);
    temp.push_back(init);
      
    // Now iterate
    for (int i = 2; i <= length; i++) {
        std::vector<long> all;
        std::vector<long> end_in_zero = temp[i-1];
        std::vector<long> end_in_one = temp[i-2];

        for (int j = 0; j < end_in_zero.size(); j++) {
          end_in_zero[j] = end_in_zero[j] << 1; // Generate sequences ending in zero
        }

        for (int j = 0; j < end_in_one.size(); j++) {
          end_in_one[j] = (end_in_one[j] << 2) + 1; // Generate sequences ending in one
        }
        all.insert(all.end(), end_in_zero.begin(), end_in_zero.end());
        all.insert(all.end(), end_in_one.begin(), end_in_one.end());
        temp.push_back(all);
        // cout << "Size " << all.size() << endl;
        // cout << "Size of array " << temp.size() << endl; 
    }
    return temp[length];
}
std::vector<long> generate_new_sequences(int length) {
    // Create the array of fibonnaci numbers
    int array[length+3];
    array[1] = 1;
    array[2] = 2;
    for (int i = 3; i < length+3; i++){
        array[i] = array[i-1] + array[i-2];
    }
    // Initialize the array
    std::vector<long> init;
    init.push_back(0);   
    init.push_back(1);
    int pos;  
    // Now iterate
    for (int i = 2; i <= length; i++) {
        int pos = array[i+2] - 1;
        int end = array[i-1];
        for (int j = 0; j <end; j++) {
            init.push_back(init[j] | (1 << i - 1)); 
        }            
    }
    return init;
}

std::vector<long> generate_ring_sequences(int length) {
    
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
         std::vector<long>  end_in_zero = generate_new_sequences(length - 1);
         std::vector<long> end_in_one = generate_new_sequences(length - 3);
          for (int i = 0; i < end_in_zero.size(); i++) {
              end_in_zero[i] = (end_in_zero[i] << 1);
          }
          for (int i = 0; i < end_in_one.size(); i++) {
              end_in_one[i] = (end_in_one[i] << 2) + 1;
          }
        ret.insert(ret.end(), end_in_zero.begin(), end_in_zero.end());
        ret.insert(ret.end(), end_in_one.begin(), end_in_one.end());
    }
   return ret;
}

Eigen::MatrixXd generate_matrix(int length) {
    std::vector<long> sequences = generate_sequences(length);
    int size = sequences.size();
    Eigen::MatrixXd transfer(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { 
             transfer(i,j) = !(sequences[i] & sequences[j]);
       }
    }
   // cout << transfer << endl;
    return transfer;
}

Eigen::MatrixXd generate_matrix_new(int length) {
    std::vector<long> sequences = generate_sequences(length);
    int size = sequences.size();
    Eigen::MatrixXd transfer(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) { 
             int val = !(sequences[i] & sequences[j]);
             transfer(i,j) = val;
             transfer(j,i) = val;
       }
    }
    //cout << transfer << endl;
    return transfer;
}
Eigen::MatrixXd generate_matrix_ring(int length) {
    std::vector<long> sequences = generate_ring_sequences(length);
    int size = sequences.size();
    Eigen::MatrixXd transfer(size, size);
    transfer.fill(0);
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) { 
             int val = !(sequences[i] & sequences[j]);
             transfer(i,j) = val;
             transfer(j,i) = val;
       }
    }
    //cout << transfer << endl;
    return transfer;
}
Eigen::MatrixXd generate_matrix_new_s(int length) {
    std::vector<long> sequences = generate_new_sequences(length);
    int size = sequences.size();
    Eigen::MatrixXd transfer(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) { 
             int val = !(sequences[i] & sequences[j]);
             transfer(i,j) = val;
             transfer(j,i) = val;
       }
    }
    //cout << transfer << endl;
    return transfer;
}


double transfer_eigenvalue(Eigen::MatrixXd matrix) {
    // Naive implementation of the power method
    int rows = matrix.rows();
    Eigen::VectorXd evec(rows); 
    evec.fill(1); 
    Eigen::VectorXd new_vec = matrix * evec;
    double old_eigen;
 
    old_eigen = 0;
    new_vec.normalize();
    evec.normalize();
    double  eigen_guess =evec.dot(matrix * evec);

  //  cout << "Guess of eigenvalue " << setprecision(16) << eigen_guess << endl; 
 //   cout << "old eigen " << setprecision(16) << old_eigen << endl;
 //   cout << "epsilon = " << numeric_limits<double>::epsilon() <<endl;
 //   cout << "error of eigenvalue " << setprecision(16) <<  abs(eigen_guess-old_eigen)  << endl; 

    while ( abs(eigen_guess-old_eigen) >  numeric_limits<double>::epsilon() ){
    //    cout << "error of eigenvalue " << setprecision(16) <<  abs(eigen_guess-old_eigen)  << endl; 
        new_vec = matrix * evec;
       
        new_vec.normalize();
        evec = new_vec;
//         cout << evec << endl;
        old_eigen = eigen_guess;
        eigen_guess = new_vec.dot(matrix * new_vec);
//        cout << "Guess of eigenvalue " << setprecision(16) << eigen_guess << endl; 
//       cout << "upper bound on eigenvalue " << setprecision(16) << eigen_upper << endl; 
//        cout << "old_eigen " << setprecision(16) << old_eigen << endl; 

    }
    return eigen_guess;
}
double transfer_eigenvalue_upper(Eigen::MatrixXd matrix) {
    // Naive implementation of the power method
    int rows = matrix.rows();
    Eigen::VectorXd evec(rows); 
    evec.fill(1); 
    Eigen::VectorXd new_vec = matrix * evec;
    double eigen_upper = -1;
    double old_eigen;
    double sample;
    double dif = 1;
    double delta;
    old_eigen = 0;
    new_vec.normalize();
    evec.normalize();
  // cout << "old eigen " << setprecision(16) << old_eigen << endl;
 //   cout << "epsilon = " << numeric_limits<double>::epsilon() <<endl;

    while ( abs(eigen_upper-old_eigen) > numeric_limits<double>::epsilon() && abs(dif-delta) > numeric_limits<double>::epsilon()) {
    //    cout << "error of eigenvalue " << setprecision(16) <<  abs(eigen_guess-old_eigen)  << endl; 
    dif = delta;
     delta = abs(eigen_upper - old_eigen);
        new_vec = matrix * evec;
        old_eigen = eigen_upper;
        eigen_upper = 0;
        for (int i = 0; i < rows; i ++){
            sample = new_vec(i)/evec(i);
            if (sample > eigen_upper)
                eigen_upper = sample;
        }  
        new_vec.normalize();
        evec = new_vec;
//         cout << evec << endl;
//       cout << "upper bound on eigenvalue " << setprecision(16) << eigen_upper << endl; 
//        cout << "old_eigen " << setprecision(16) << old_eigen << endl; 

    }
    return eigen_upper;
}

int main(int argc, char* argv[]) {
    int length = atoi(argv[1]);   
    cout << " generating matrix " << endl;
    clock_t t = clock();
    MatrixXd matrix = generate_matrix_ring(length);
    double eig = transfer_eigenvalue(matrix);
    t = clock() - t;
    cout << " Eigenvalue " << setprecision(16) << eig << endl;
    cout << " Bound " << pow(eig, 1.0/ length) << endl;
    cout << " time " << t << endl;
    cout << (float) t/ CLOCKS_PER_SEC << " seconds" << endl; 
}
