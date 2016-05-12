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
    double eigen_upper;
    double old_eigen;
    double sample = (double) new_vec(1) / evec(1);
 
    eigen_upper = (double) new_vec(0) / evec(0);

    for (int i = 1; i < rows; i ++){
        sample = (double) new_vec(i) / evec(i);
        if (sample > eigen_upper)
            eigen_upper = sample;
    }
    
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
        for (int i = 1; i < rows; i ++){
            sample = new_vec(i)/evec(i);
            if (sample > eigen_upper)
                eigen_upper = sample;
        }
       
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



int main(int argc, char* argv[]) {
//    clock_t t = clock();
   int length = atoi(argv[1]);   
//   cout << " generating old sequences " << endl;
   std::vector<long> sequences = generate_sequences(length);
   std::sort (sequences.begin(), sequences.end());
//   cout << " generating new sequences " << endl;
   std::vector<long> new_sequences = generate_new_sequences(length);
   int error=0;
   for (int i = 0; i < new_sequences.size(); i++){
       error+= abs(sequences[i]-new_sequences[i]);
    }
    cout << error << endl;
   /*
   cout << " sizes " << endl;
   for (int i = 1; i <= length; i++){
       cout << generate_new_sequences(i).size() << endl;
   }
   */
 //   t = clock() - t;
  //  cout << (float) t/ CLOCKS_PER_SEC << " seconds" << endl;

   // clock_t t_new = clock();
   // generate_matrix_new(atoi(argv[1]));
   // t_new = clock() - t_new;
    //cout << (float) t_new/ CLOCKS_PER_SEC << " seconds" << endl; 
  //  double eig =  transfer_eigenvalue(generate_matrix(atoi(argv[1])));
  // cout << setprecision(16) << eig << endl;
}

