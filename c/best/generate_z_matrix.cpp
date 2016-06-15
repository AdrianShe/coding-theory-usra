#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "fib.h"
#include "multiply_t.h"
#include "sequences_linear_one_dim.h"
#include "sequences_ring_one_dim.h"
#include "compute_eigen_value_one_dim.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>
#include <fstream>
#include <string>     // std::string, std::to_string


using namespace std;
using namespace Eigen;

int digit_sum(long seq){
    int ret = 0;
    for (int i = 0; i < 32; i++){
       if ((seq >> i) % 2 == 1) ret++;
    }
    return ret;
} 

std::vector<int> generate_counts(std::vector<long> seqs){
    std::vector<int> ret;
    int size = seqs.size();
    ret.resize(size);
    for (int i = 0; i < size; i++){
        ret[i] = digit_sum(seqs[i]);
    }
    return ret;
}

Eigen::MatrixXd generate_z_matrix_helper(int length, std::vector<long> seqs, double z, std::vector<int> counts){
//    cout << " in helper " << endl;
    int size = seqs.size();
    std::vector<double> z_counts;
    z_counts.resize(size);
//    cout << counts.size() << endl;
    for (int k = 0; k<counts.size(); k++){
//        cout << " in loop k = " << k << endl;
//        cout << z_counts[k] << endl;
 //       cout << counts[k] << endl;
        z_counts[k] = pow(z, counts[k]);
    }
//    cout << " prepared count " << endl;
    Eigen::MatrixXd ret(size,size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
             if ((seqs[i] & seqs[j]) == 0){
                ret(i,j) = z_counts[i];
                ret(j,i) = z_counts[j];
             }   
        }
    }
    return ret;
}

Eigen::MatrixXd generate_z_matrix_expander_helper(int length, std::vector<long> seqs, std::vector<long> seqs_2, double z, std::vector<int> counts){
//    cout << " in helper " << endl;
    int size = seqs.size();
    int size_2 = seqs_2.size();
    std::vector<double> z_counts;
    z_counts.resize(size_2);
   for (int k = 0; k < size_2; k++){
       z_counts[k] = pow(z, counts[k]);
    }
//    cout << " prepared count " << endl;
    Eigen::MatrixXd ret(size_2,size);
    ret.fill(0);
    for (int i = 0; i < size_2; i++){
        for (int j = 0; j < size; j++){
             if ((seqs_2[i] & seqs[j]) == 0){
                ret(i,j) = z_counts[i];    
             }
        }       
    }
    return ret;
}
Eigen::MatrixXd generate_z_matrix_expander(int length, double z){
    std::vector<long> seqs = generate_linear_one_dim_sequences(length);
    std::vector<long> seqs_2 = generate_linear_one_dim_sequences(length+1);
    return generate_z_matrix_expander_helper(length, seqs,seqs_2, z, generate_counts(seqs_2));
}

Eigen::MatrixXd generate_z_matrix(int length, double z){
    std::vector<long> seqs = generate_linear_one_dim_sequences(length);
    return generate_z_matrix_helper(length,seqs ,z , generate_counts(seqs));
}



                
                     
double brian_constant(int a , int b , int c, double z, std::vector<long> seqs, std::vector<long> seqs_2  ){
    int size = seqs.size();
    int size_2 = seqs_2.size();
    Eigen::VectorXd vec(size);
    std::vector<int> counts = generate_counts(seqs);
    for (int k = 0; k < size; k++){
       vec(k) = pow(z, counts[k]);
    }
    Eigen::VectorXd vec_t = vec;
    Eigen::VectorXd vec_b = vec;
    std::vector<int> counts_2 = generate_counts(seqs_2);
    Eigen::MatrixXd T_a = generate_z_matrix_helper(a, seqs, z, counts);
    Eigen::MatrixXd E_a = generate_z_matrix_expander_helper(a, seqs, seqs_2, z, counts_2);
    Eigen::MatrixXd T_a_1 = generate_z_matrix_helper(a+1, seqs_2, z, counts_2);   
   if ( a>=10 ){
   ofstream matrix ("new.txt"); 
    matrix << "Matrices for a = " << a << endl;
    matrix << T_a << endl;
    matrix << endl;
    matrix << E_a << endl;
    matrix << endl;
    matrix << T_a_1 << endl;
    }
    for (int i = 0; i < b -1; i++){
        vec_t = T_a*vec_t;
    }
    vec_b = T_a*vec_t;
    Eigen::VectorXd vec_b_new = E_a*vec_b;
    Eigen::VectorXd vec_t_new = E_a*vec_t;
    for (int i = 0; i < c-2; i++){
        vec_t_new = T_a_1*vec_t_new;
        vec_b_new = T_a_1*vec_b_new;
    }
    vec_t_new = T_a_1*vec_t_new;

       return vec_t_new.sum()/vec_b_new.sum();
}
/*
double andrew_constant (int a , int b , int c){
//    cout << "a = " << a << endl;//
//    cout << "b = " << b << endl;//
//    cout << "c = " << c << endl;//
  // Do original system
    int fib_t = fib(c+2);
    int fib_tb = fib (b+c+2);
    Eigen::VectorXd top(fib_t);
    Eigen::VectorXd bottom(fib_tb-fib_t);
    top.fill(1);
    bottom.fill(0);
    Eigen::VectorXd vec(fib_tb);
   vec << top, bottom; 
    std::vector<long>seqs =  generate_linear_one_dim_sequences(b+c);  
    vec = multiply_t_helper(b+c,seqs, vec, a);
    // Remove one square
    int fib_t_new = fib(c+1);
    Eigen::VectorXd top_new(fib_t_new);
    Eigen::VectorXd bottom_new(fib_tb-fib_t_new);
    top_new.fill(1);
    bottom_new.fill(0);
    Eigen::VectorXd vec_new(fib_tb);
   vec_new << top_new, bottom_new;
      vec_new = multiply_t_helper(b+c,seqs,vec_new, a);
    // Return eta approx (?)
    return vec.sum()/vec_new.sum();
 
    //Creates an instance of ofstream, and opens example.txt
   //    // Outputs to example.txt through a_file
    //      a_file<<"This text will now be inside of example.txt";
    //        // Close the file stream explicitly
    //          a_file.close();}
*/
int main(int argc, char* argv[]) {
    int a_end = atoi(argv[1]);
    int b_end = atoi(argv[2]);
    int c_end = atoi(argv[3]);
    ofstream output ( "gen.txt" );
   
    double z_end = atof(argv[4]);
    for (int a = a_end; a >= 1; a--){
        std::vector<long> seqs = generate_linear_one_dim_sequences(a);
        std::vector<long> seqs_2 = generate_linear_one_dim_sequences(a+1);
        output << left << setw(4) << "a" << setw(4) << "b" << setw(4) <<"c" << setw(4) << "z"<< setw(18) << "bc"  << endl;
 
        for (int b = b_end; b<=b_end; b++){
            for (int c = c_end; c<=c_end; c++){
               for (double z = z_end; z<=z_end; z*=2){ 
                    output << setprecision(16) << left << setw(4) <<  a << setw(4) << b << setw(4) << c << setw(4) << z << setw(18) <<  brian_constant(a,b,c,z, seqs, seqs_2) << endl;
                }
            }
        }
    }
}

