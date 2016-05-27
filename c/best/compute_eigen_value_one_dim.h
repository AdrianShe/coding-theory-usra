#ifndef CEVO_INCLUDED
#define CEVO_INCLUDED
#include <vector>
#include <utility> 
double compute_eigen_linear_one_dim_upper(int length); 
double compute_eigen_ring_one_dim_lower(int length);
double compute_eigen_linear_one_dim_lower(int length); 
double compute_eigen_ring_one_dim_upper(int length);
double compute_eigen_lower_one_dim_helper(int length, std::vector<long> seqs);
double compute_eigen_upper_one_dim_helper(int length, std::vector<long> seqs);
#endif


