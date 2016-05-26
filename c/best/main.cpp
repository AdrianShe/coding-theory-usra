#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "compute_eigen_value_two_dim.h"
#include "compute_eigen_value_one_dim.h"
#include "time.h"
#include <iomanip>      // std::setprecision

using namespace std;

int main(int argc, char* argv[]) {
    int p = atoi(argv[1]);
    int q = atoi(argv[2]);
    cout << setprecision(16) << "p = " << p << ", q = " << q << endl;
    cout << " 2 D !!! " <<  endl;
    cout << " Power Method Results !! " << endl;
   
    clock_t t = clock();
    double eig_nume =  compute_eigen_linear_two_dim_lower(p+2*q+1);
    double eig_denom = compute_eigen_linear_two_dim_upper(2*q+1);
    double lower_bound = pow(eig_nume / eig_denom, 1.0 / p);
    t = clock() - t;
    cout << "The calkin lower bound is " << lower_bound  << " in time " << t << endl;
    
    t = clock();
    eig_nume =  compute_eigen_ring_two_dim_lower(p+2*q);
    eig_denom = compute_eigen_ring_two_dim_upper(2*q);
    lower_bound = pow(eig_nume / eig_denom, 1.0 / p);
    t = clock() - t;
    cout << "The friedland lower bound is " << lower_bound  << " in time " << t << endl;
 
    t = clock();
    double eig = compute_eigen_ring_two_dim_upper(2*p); 
    double upper_bound = pow(eig, 1.0 / (2*p));
    t = clock() - t;
    cout <<"The upper bound is " << upper_bound << " in time " << t << endl; 
    
    cout << " 1 D !!! "<<  endl;
    cout << " Power Method Results !! " << endl;
    
    t = clock();
    eig_nume =  compute_eigen_linear_one_dim_lower(p+2*q+1);
    eig_denom = compute_eigen_linear_one_dim_upper(2*q+1);
    lower_bound = pow(eig_nume / eig_denom, 1.0 / p);
    t = clock() - t;
    cout << "The calkin lower bound is " << lower_bound  << " in time " << t << endl;
    
    t = clock();
    eig_nume =  compute_eigen_ring_one_dim_lower(p+2*q);
    eig_denom = compute_eigen_ring_one_dim_upper(2*q);
    lower_bound = pow(eig_nume / eig_denom, 1.0 / p);
    t = clock() - t;
    cout << "The friedland lower bound is " << lower_bound  << " in time " << t << endl;
 
 
    t = clock();
    eig = compute_eigen_ring_one_dim_upper(2*p); 
    upper_bound = pow(eig, 1.0 / (2*p));
    t = clock() - t;
    cout <<"The upper bound is " << upper_bound << " in time " << t << endl; 


}


