#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include "generate.h"
#include "fib.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
    int p = atoi(argv[1]);
    int q = atoi(argv[2]);

    MatrixXf T_p = generate_matrix(p + 2 * q + 1); 
    MatrixXf T_q = generate_matrix(2 * q + 1);

    //cout << T_p << endl;
    // cout << T_q << endl;

    Eigen::SelfAdjointEigenSolver<MatrixXf> ep(T_p);
    Eigen::SelfAdjointEigenSolver<MatrixXf> eq(T_q);

    int index_p = fib(p + 2 * q + 3) - 1;
    int index_q = fib(2 * q + 3) - 1;
    
   // cout << " Evecs p \n" << ep.eigenvalues() << endl;
   // cout << " Evecs q \n" << eq.eigenvalues() << endl;
   // cout << index_p << " " << index_q << endl;
    double dp = ep.eigenvalues()[index_p];
    double dq = eq.eigenvalues()[index_q];
 
    cout << " Dominant eigenvalue of T_(p+2q) \n" << setprecision(16) << dp << endl;
    cout << " Dominant eigenvalue of T_2q \n" << dq  << endl;
    // cout << " Ratio of evecs " << dp / dq << endl;
    double bound = pow(dp / dq, 1.0 / p);
    cout << "The bound is " << bound  << endl;
}
