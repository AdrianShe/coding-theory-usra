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

using namespace std;
using namespace Eigen;

Eigen::VectorXd multiply_t(int length, Eigen::VectorXd vec){
    return multiply_t_helper(length, generate_linear_one_dim_sequences(length), vec, 1);
}    
Eigen::VectorXd multiply_t_helper(int length, std::vector<long> seqs, Eigen::VectorXd vec, int times){    
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    for (int k = 0; k < times; k++){ 
        ret.fill(0);
        for (int i = 0; i < size; i++){
            long sample = seqs[i];
            for (int j = i; j < size; j++){
                long comp = seqs[j];
                if (!(sample & comp)){
                    ret(i)+=vec(j);
                    if( i != j) ret(j)+=vec(i);
                }
            }
         }
         vec = ret;
   }
    return ret;
}

Eigen::VectorXd multiply_e_helper(int length, std::vector<long> seqs, std::vector<long> seqs_2,  Eigen::VectorXd vec){
    int h = seqs_2.size();
    int w = seqs.size();
    Eigen::VectorXd ret(h); 
    ret.fill(0);
    for (int i = 0; i < w; i++){
        long sample = seqs[i];
        for (int j = 0; j < h; j++){
            long comp = seqs_2[j];
            if (!(sample & comp)){
                ret(j)+=vec(i);
            }
         }
    }
    vec = ret;  
    return ret;
}

double brian_constant(int a , int b , int c){
/*    cout << "a = " << a << endl;//
    cout << "b = " << b << endl;//
    cout << "c = " << c << endl;//
*/    Eigen::VectorXd vec(fib(a + 2));
    vec.fill(1);
/*  cout << " BEFORE " << endl;
    cout << vec << endl;
    cout << endl;
    cout << "AFTER T" << endl;
*/  
    std::vector<long>seqs =  generate_linear_one_dim_sequences(a);
    std::vector<long>seqs_2 = generate_linear_one_dim_sequences(a+1);  
    vec = multiply_t_helper(a,seqs, vec, b-1);  
//    cout << vec << endl; 
//    cout << "AFTER E" << endl;
    Eigen::VectorXd new_vec = multiply_e_helper(a, seqs, seqs_2, vec);  
//    cout << new_vec << endl;    
//    cout << "AFTER T" << endl;
    new_vec = multiply_t_helper(a+1, seqs_2, new_vec, c-1);  
//    cout << new_vec << endl; 
    vec = multiply_t_helper(a,seqs,vec, 1); 
    Eigen::VectorXd keep_vec = multiply_e_helper(a,seqs,seqs_2,vec);
    keep_vec = multiply_t_helper(a+1,seqs_2,keep_vec, c-2);
    cout << "Numerator: " << new_vec.sum() << endl;
    cout << "Denominator: " << keep_vec.sum() << endl;
    return new_vec.sum()/keep_vec.sum();
}

int main(int argc, char* argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    cout << a << " " << b << " " <<  c << " " << setprecision(16) << brian_constant(a,b,c) << endl;
}   



