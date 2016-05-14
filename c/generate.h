#ifndef _GENERATE_
#define _GENERATE_
#include <vector>
#include <Eigen/Dense>
#include "time.h"

std::vector<long> generate_sequences(int length);
std::vector<long> generate_new_sequences(int length);
std::vector<long> generate_ring_sequences(int length);
Eigen::MatrixXd generate_matrix(int length);
Eigen::MatrixXd generate_matrix_new(int length);
Eigen::MatrixXd generate_matrix_new_s(int length);
Eigen::MatrixXd generate_matrix_ring(int length);
double transfer_eigenvalue(Eigen::MatrixXd matrix);
double transfer_eigenvalue_upper(Eigen::MatrixXd matrix);
double circular_eigenvalue_implicit(std::vector<long> sequences);
#
#endif 
