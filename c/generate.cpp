#include <vector>
#include <Eigen/Dense>
#include "generate.h"
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

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

double transfer_eigenvalue(Eigen::MatrixXd matrix) {
    // Naive implementation of the power method
    Eigen::VectorXd evec(matrix.rows()); 
    evec.fill(1); 
    
    double eigen_guess;
    for (int i = 1; i < 1000; i++) {
        Eigen::VectorXd new_vec = matrix * evec;
        new_vec.normalize();
        evec = new_vec;
        // cout << evec << endl;
        eigen_guess = evec.dot(matrix * evec);
        // cout << "Guess of eigenvalue " << setprecision(16) << eigen_guess << endl; 
    }
    return eigen_guess;
}

int main(int argc, char* argv[]) {
//    clock_t t = clock();
    generate_matrix(atoi(argv[1]));
 //   t = clock() - t;
  //  cout << (float) t/ CLOCKS_PER_SEC << " seconds" << endl;

   // clock_t t_new = clock();
    generate_matrix_new(atoi(argv[1]));
   // t_new = clock() - t_new;
    //cout << (float) t_new/ CLOCKS_PER_SEC << " seconds" << endl; 
    double eig =  transfer_eigenvalue(generate_matrix(atoi(argv[1])));
   cout << setprecision(16) << eig << endl;
}

