#ifndef SRT_INCLUDED
#define SRT_INCLUDED
#include <vector>
#include <utility> 
std::vector<std::pair<long,long> > generate_ring_two_dim_sequences(int length); 
std::vector<std::pair<long,long> > keep_two_dim_rings(std::vector<std::pair<long,long> > seqs, int length);
bool is_two_dim_ring(std::pair<long,long> sample, int length);
#endif


