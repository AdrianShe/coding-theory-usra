#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "compute_eigen_value.h"
#include "time.h"
#include <iomanip>      // std::setprecision

using namespace std;

int main(int argc, char* argv[]) {
    int p = atoi(argv[1]);
    int q = atoi(argv[2]);
    cout << setprecision(16) << "p = " << p << ", q = " << q << endl;
  cout << " Power Method Results !! " << endl;
    clock_t t = clock();
    double eig_nume =  compute_eigen_linear_lower(p+2*q+1);
    double eig_denom = compute_eigen_linear_upper(2*q+1);
    double lower_bound = pow(eig_nume / eig_denom, 1.0 / p);
    t = clock()-t;
   cout << "The lower bound is " <<lower_bound  << " in time " << t << endl;
    t = clock();
    double eig = compute_eigen_ring_upper(2*p); 
    double upper_bound = pow(eig, 1.0 / (2*p));
    t = clock()-t;
    cout <<"The upper bound is " << upper_bound << " in time " << t << endl; 

}


