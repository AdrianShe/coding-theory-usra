#ifndef _GENERATE_
#define _GENERATE_
#include <vector>
#include <Eigen/Dense>
#include "time.h"

std::vector<long> generate_sequences(int length);
Eigen::MatrixXf generate_matrix(int length);
Eigen::MatrixXf generate_matrix_new(int length);
double transfer_eigenvalue(Eigen::MatrixXf matrix);
#endif 