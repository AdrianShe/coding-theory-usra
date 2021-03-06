#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include "generate.h"
#include "fib.h"
#include "generate_2.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
    int p = atoi(argv[1]);
    int q = atoi(argv[2]);
/*
    MatrixXd T_p = generate_matrix(p + 2 * q + 1); 
    MatrixXd T_q = generate_matrix(2 * q + 1);
*/  
/*
    MatrixXd T_p = generate_matrix_new(p + 2 * q + 1); 
    MatrixXd T_q = generate_matrix_new(2 * q + 1);
*/
    MatrixXd T_p = generate_matrix_2(p + 2 * q + 1); 
    MatrixXd T_q = generate_matrix_2(2 * q + 1);



//     cout << T_p << endl;
//     cout << T_q << endl;

    Eigen::SelfAdjointEigenSolver<MatrixXd> ep(T_p);
    Eigen::SelfAdjointEigenSolver<MatrixXd> eq(T_q);

    int index_p = fib(p + 2 * q + 3) - 1;
    int index_q = fib(2 * q + 3) - 1;
    
   // cout << " Evecs p \n" << ep.eigenvalues() << endl;
   // cout << " Evecs q \n" << eq.eigenvalues() << endl;
   // cout << index_p << " " << index_q << endl;
    double dp = ep.eigenvalues()[index_p];
    double dq = eq.eigenvalues()[index_q];
    cout << " EigenSolver Results !! " << endl;
    cout << " Dominant eigenvalue of T_(p+2q) \n" << setprecision(16) << dp << endl;
    cout << " Dominant eigenvalue of T_2q \n" << dq  << endl;
    // cout << " Ratio of evecs " << dp / dq << endl;
    double bound = pow(dp / dq, 1.0 / p);
    cout << "The bound is " << bound  << endl;

   cout << " Power Method Results !! " << endl;
 
   
    double eigp =  transfer_eigenvalue(T_p);
    double eigq = transfer_eigenvalue(T_q);
    double eigp_u =  transfer_eigenvalue_upper(T_p);
    double eigq_u = transfer_eigenvalue_upper(T_q);
    cout << " Dominant eigenvalue of T_(p+2q) is greater than \n" << setprecision(16) << eigp << endl;
    cout << " Dominant eigenvalue of T_2q is greater than \n" << eigq  << endl;
    cout << " Dominant eigenvalue of T_(p+2q) is less than \n" << setprecision(16) << eigp_u << endl;
    cout << " Dominant eigenvalue of T_2q is less than \n" << eigq_u  << endl;
 
    bound = pow(eigp / eigq_u, 1.0 / p);
    cout << "The bound is " << bound  << endl;

    cout << " Time Results !! " << endl;
 
    clock_t t_new = clock();
    generate_matrix_2(atoi(argv[1]));
    t_new = clock() - t_new;
    cout << (float) t_new/ CLOCKS_PER_SEC << " seconds for new method" << endl; 
    clock_t t = clock();
    generate_matrix(atoi(argv[1]));
    t = clock() - t;
    cout << (float) t/ CLOCKS_PER_SEC << " seconds for old method" << endl; 
 
}


