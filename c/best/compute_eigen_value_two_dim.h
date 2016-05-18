#ifndef CEVT_INCLUDED
#define CEVT_INCLUDED
#include <vector>
#include <utility> 
double compute_eigen_linear_two_dim_upper(int length); 
double compute_eigen_ring_two_dim_lower(int length);
double compute_eigen_linear_two_dim_lower(int length); 
double compute_eigen_ring_two_dim_upper(int length);
double compute_eigen_lower_two_dim_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs);
double compute_eigen_upper_two_dim_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs);
#endif


