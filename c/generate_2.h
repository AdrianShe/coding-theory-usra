#ifndef _GENERATE2_
#define _GENERATE2_
#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include <utility>

std::vector<std::pair<long,long> > generate_2_sequences(int length);
Eigen::MatrixXd generate_matrix_2(int length);
double generate_eigen(int length);
double generate_eigen_upper(int length);
#endif 
