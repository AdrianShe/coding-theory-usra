#ifndef CEV_INCLUDED
#define CEV_INCLUDED
#include <vector>
#include <utility> 
double compute_eigen_linear_upper(int length); 
double compute_eigen_ring_lower(int length);
double compute_eigen_linear_lower(int length); 
double compute_eigen_ring_upper(int length);
double compute_eigen_lower_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs);
double compute_eigen_upper_helper(int length, std::vector<long> table, std::vector<std::pair<long,long> > seqs);
#endif


