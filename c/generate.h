#ifndef _GENERATE_
#define _GENERATE_
#include <vector>
#include <Eigen/Dense>
#include "time.h"

std::vector<long> generate_sequences(int length);
std::vector<long> generate_new_sequences(int length);
Eigen::MatrixXd generate_matrix(int length);
Eigen::MatrixXd generate_matrix_new(int length);
Eigen::MatrixXd generate_matrix_new_s(int length);
double transfer_eigenvalue(Eigen::MatrixXd matrix);
double transfer_eigenvalue_upper(Eigen::MatrixXd matrix);
#
#endif 
