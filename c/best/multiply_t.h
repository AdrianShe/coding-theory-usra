#ifndef MUlT_T_INCLUDED
#define MULT_T_INCLUDED
#include <vector>
#include <utility>
#include <Eigen/Dense>
Eigen::VectorXd multiply_t(int length, Eigen::VectorXd vec);
Eigen::VectorXd multiply_t_helper(int length, std::vector<long> seqs, Eigen::VectorXd vec, int times);
#endif


