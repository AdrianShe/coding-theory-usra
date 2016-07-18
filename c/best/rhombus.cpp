#include <vector>
#include <Eigen/Dense>
#include "time.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include "fib.h"
#include "multiply_t.h"
#include "sequences_linear_one_dim.h"
#include "sequences_ring_one_dim.h"
#include "compute_eigen_value_one_dim.h"
#include <utility>      // std::pair, std::make_pair
#include <map>
#include <limits>
#include <bitset>
#include <fstream>
#include <string>     // std::string, std::to_string
#include <assert.h>     /* assert */
#include "time.h"


using namespace std;
using namespace Eigen;

int digit_sum(long seq){
    int ret = 0;
    for (int i = 0; i < 32; i++){
       if ((seq >> i) % 2 == 1) ret++;
    }
    return ret;
}

bool is_valid(long seq){
    for (int i = 1; i < 32; i++){
        if (((seq >> i) & (seq >> (i-1))) % 2 == 1)
            return false;
    }
    return true;
}

//returns whether seq_2 can follow seq_2
bool is_compatible(long seq_1, long seq_2){
    std::bitset<32> alt_bit (std::string("01010101010101010101010101010101"));
    long alt = alt_bit.to_ulong();
    long check = (seq_1 & alt)|seq_2;
    return is_valid(check);
}

std::vector<int> generate_counts(std::vector<long> seqs){
    std::vector<int> ret;
    int size = seqs.size();
    ret.resize(size);
    for (int i = 0; i < size; i++){
        ret[i] = digit_sum(seqs[i]);
    }
    return ret;
}

Eigen::VectorXd multiply_z_matrix(std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}


bool is_mid(long seq, int n){
    long mid = 1 << n;
    if ((seq & mid) == 0 ) return true;
    return false;
}

bool is_bot(long seq, int n){
    long bot = 1 << 2*n;
    if ((seq & bot) == 0 ) return true;
    return false;
}

bool is_top(long seq){
    long top = 1;
    if ((seq & top) == 0 ) return true;
    return false;
}

bool is_start(long seq){
    std::bitset<32> alt_bit (std::string("10101010101010101010101010101010"));
    long alt = alt_bit.to_ulong(); 
    if ((seq & alt) == 0) return true;
    return false;
}

bool is_start_m(long seq, int m){
    int start = 0;
    if (!is_start(seq)) return false; 
    for (int i = 0; i < m; i++){
        long temp = 1 << (2*i);
        start = start | temp;
    }
   if ((seq & start) == 0) return true;
    return false;  
}

bool is_end_m(long seq, int m){
    long end = 0;
    for (int i = 0; i < m; i++){
        long temp = 1 << (2*i);
        end = end | temp;
    }
    if ((seq & end) == 0) return true;
    return false;  
}



Eigen::VectorXd multiply_z_matrix_b(int n, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_bot(seqs[j], n)) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}

Eigen::VectorXd multiply_z_matrix_c(int n, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_mid(seqs[j], n)) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}

Eigen::VectorXd multiply_z_matrix_ct(int n, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_mid(seqs[j], n) && is_top(seqs[j])) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}

Eigen::VectorXd multiply_z_matrix_t(std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_top(seqs[j])) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}

Eigen::VectorXd multiply_z_matrix_ctb(int n, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_mid(seqs[j], n) && is_top(seqs[j]) && is_bot(seqs[j], n)) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}
Eigen::VectorXd multiply_z_matrix_tb(int n, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_top(seqs[j]) && is_bot(seqs[j], n)) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}


Eigen::VectorXd multiply_z_matrix_e(int m, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_end_m(seqs[j], m)) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}

Eigen::VectorXd multiply_z_matrix_eb(int n, int m, std::vector<long> seqs, std::vector<double> z_counts, Eigen::VectorXd vec){
    int size = seqs.size();
    Eigen::VectorXd ret(size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i], seqs[j])){
                if (is_end_m(seqs[j], m) && is_bot(seqs[j],n)) ret(j)+= z_counts[j]*vec(i);
            }
        }
    }
    return ret;
}

Eigen::MatrixXd generate_z_matrix_helper(std::vector<long> seqs, double z, std::vector<int> counts){
    int size = seqs.size();
    std::vector<double> z_counts;
    z_counts.resize(size);
    for (int k = 0; k<counts.size(); k++){
        z_counts[k] = pow(z, counts[k]);
    }
    Eigen::MatrixXd ret(size,size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (is_compatible(seqs[i],seqs[j])){
                ret(j,i) = z_counts[j];
            }   
        }
    }
    return ret;
}

Eigen::MatrixXd generate_z_matrix_2_helper(int n, Eigen::MatrixXd mat, std::vector<long> seqs){
    for (int i = 0; i < seqs.size(); i++){
        if (!is_mid(seqs[i], n))
            mat.row(i).fill(0);
    }
    return mat;
}

Eigen::VectorXd generate_init(double z, std::vector<long> seqs, std::vector<int> counts){
    Eigen::VectorXd init(seqs.size());
    init.fill(0);
    for (int k = 0; k<counts.size(); k++){
        if (is_start(seqs[k])){
            init(k) = pow(z, counts[k]);
        }
    }
    return init;
}

Eigen::VectorXd generate_init_m(int m, double z, std::vector<long> seqs, std::vector<int> counts){
    Eigen::VectorXd init(seqs.size());
    init.fill(0);
    for (int k = 0; k<counts.size(); k++){
        if (is_start_m(seqs[k], m)){
            init(k) = pow(z, counts[k]);
        }
    }
    return init;
}

double probability_rhombus(int n, Eigen::MatrixXd mat, Eigen::MatrixXd mat_2, Eigen::VectorXd init){
    Eigen::VectorXd vec = init; 
    for (int i = 1; i < (n+1)/2; i++){
        vec = mat*vec;
    }
   init = mat_2*vec;
    vec = mat*vec;
   for (int j = 1; j <= n-(n+1)/2; j++){
        init = mat*init;
        vec = mat*vec;
    }
   return init.sum()/vec.sum();
}
 
double probability_rhombus_imp_omit(int a, double z, int n, std::vector<int> counts, std::vector<long> seqs){
    int m = n+1;
    if (a<=(n+1)) m = a;

    // remove upto n+1 elements from initial
    Eigen::VectorXd init = generate_init_m(m, z, seqs, counts);
    a-=m;
    std::vector<double> z_counts;
    int size = counts.size();
    z_counts.resize(size); 

    for (int k = 0; k<counts.size(); k++){
        z_counts[k] = pow(z, counts[k]);
    }

    Eigen::VectorXd vec = init; 
    
    // remove upto middle
    for (int i = 2; i <= (n+1)/2; i++){
        if ((a>0) && (a<(3*n+3-2*i))){
            vec = multiply_z_matrix_t(seqs,z_counts,vec);
            a--;
        } else if (a <= 0) {
            vec = multiply_z_matrix(seqs, z_counts, vec);
        } else {
            vec = multiply_z_matrix_tb(n, seqs,z_counts,vec); 
            a=a-2;
        }
    }
    
    // remove middle
    if (n > 0){ 
        if (a>0 && (a<(3*n+3-2*((n+1)/2 +1) ))){
            init = multiply_z_matrix_ct(n, seqs, z_counts, vec);
            vec = multiply_z_matrix_t(seqs, z_counts,vec);
            a--;
        } else if ( a <= 0){
            init = multiply_z_matrix_c(n, seqs, z_counts, vec);
            vec = multiply_z_matrix(seqs, z_counts,vec);
        } else {
            init = multiply_z_matrix_ctb(n, seqs, z_counts, vec);
            vec = multiply_z_matrix_tb(n, seqs, z_counts,vec);
        }
    }

    // remove after middle
    for (int j = (n+1)/2+2; j <= n; j++){
        if ((a>0) && (a<(3*n+3-2*j))){
            vec = multiply_z_matrix_t(seqs,z_counts,vec);
            init = multiply_z_matrix_t(seqs, z_counts, init); 
            a--;
        } else if (a<=0){
            vec = multiply_z_matrix(seqs, z_counts, vec);
            init = multiply_z_matrix(seqs, z_counts, init);
        }
        else {
            vec = multiply_z_matrix_tb(n, seqs,z_counts,vec);
            init = multiply_z_matrix_tb(n, seqs, z_counts, init); 
            a=a-2;
        }
    }
    
    // remove final
     if (n > 1){ 
        int m = n+1;
        if (a<=(n+1)) m = a;
        init = multiply_z_matrix_e(m, seqs, z_counts, init);
        vec = multiply_z_matrix_e(m, seqs, z_counts, vec);
        a -= m;

    }
   return init.sum()/vec.sum();
}

std::vector<double> probability_rhombus_imp_omit_bulk(double z, int n, std::vector<int> counts, std::vector<long> seqs){
    assert(n>1);
    std::vector<double> out;
    out.resize(4*n+1);
 
    Eigen::VectorXd init = generate_init(z, seqs, counts);
    Eigen::VectorXd mid;
    std::vector<double> z_counts;
    int size = counts.size();

    z_counts.resize(size); 
    for (int k = 0; k<counts.size(); k++){
        z_counts[k] = pow(z, counts[k]);
    }
     // compute full
    Eigen::VectorXd vec = init; 

    for (int i = 2; i <= (n+1)/2; i++){
        vec = multiply_z_matrix(seqs, z_counts,vec);
    }

    mid = multiply_z_matrix_c(n, seqs, z_counts, vec);
    vec = multiply_z_matrix(seqs, z_counts,vec);

    for (int j = (n+1)/2+2; j <= n; j++){
        mid = multiply_z_matrix(seqs, z_counts, mid);
        vec = multiply_z_matrix(seqs, z_counts, vec);
    }
    // add full
    for (int a = 0; a <=n+1; a++){
        Eigen::VectorXd mid_2 = multiply_z_matrix_e(a, seqs, z_counts, mid);
        Eigen::VectorXd vec_2 = multiply_z_matrix_e(a, seqs, z_counts, vec);
        out[a] = mid_2.sum()/vec_2.sum();
    }

     // compute top
    init = generate_init_m(1, z, seqs, counts);  
    vec = init; 

    for (int i = 2; i <= (n+1)/2; i++){
        vec = multiply_z_matrix_t(seqs, z_counts,vec);
    }

    mid = multiply_z_matrix_ct(n, seqs, z_counts, vec);
    vec = multiply_z_matrix_t(seqs, z_counts,vec);

    for (int j = (n+1)/2+2; j <= n; j++){
        mid = multiply_z_matrix_t(seqs, z_counts, mid);
        vec = multiply_z_matrix_t(seqs, z_counts, vec);
    }
    // add top
    for (int a = 2; a <=n+1;a++){
        Eigen::VectorXd mid_2 = multiply_z_matrix_e(a, seqs, z_counts, mid);
        Eigen::VectorXd vec_2 = multiply_z_matrix_e(a, seqs, z_counts, vec);
        out[n+a] = mid_2.sum()/vec_2.sum();
    }

     // compute init
   
    init = generate_init_m(n+1, z, seqs, counts); 
    vec = init; 

    for (int i = 2; i <= (n+1)/2; i++){
        vec = multiply_z_matrix_t(seqs, z_counts,vec);
    }
    
   mid = multiply_z_matrix_ct(n, seqs, z_counts, vec);
    vec = multiply_z_matrix_t(seqs, z_counts,vec);
    
   for (int j = (n+1)/2+2; j <= n; j++){
        mid = multiply_z_matrix_t(seqs, z_counts, mid);
        vec = multiply_z_matrix_t(seqs, z_counts, vec);
    }
   // add init
    for (int a = 2; a <=n+1;a++){ 
        Eigen::VectorXd mid_2 = multiply_z_matrix_e(a, seqs, z_counts, mid);
        Eigen::VectorXd vec_2 = multiply_z_matrix_e(a, seqs, z_counts, vec);
        double prob =  mid_2.sum()/vec_2.sum();
        out[2*n+a] = prob;
        cout << 2*n + a << setw(30) << prob << endl;
    }
      // compute final
   init = generate_init_m(n+1, z, seqs, counts); 
    vec = init; 
    
    for (int i = 2; i <= (n+1)/2; i++){
        vec = multiply_z_matrix_tb(n, seqs, z_counts,vec);
    }
    
   mid = multiply_z_matrix_ctb(n, seqs, z_counts, vec);
    vec = multiply_z_matrix_tb(n, seqs, z_counts,vec);

   for (int j = (n+1)/2+2; j <= n; j++){
        mid = multiply_z_matrix_tb(n, seqs, z_counts, mid);
        vec = multiply_z_matrix_tb(n, seqs, z_counts, vec);
    }
    // add final
   for (int a = 2; a <=n;a++){
        Eigen::VectorXd mid_2 = multiply_z_matrix_eb(n,a, seqs, z_counts, mid);
        Eigen::VectorXd vec_2 = multiply_z_matrix_eb(n,a, seqs, z_counts, vec);
        double prob =  mid_2.sum()/vec_2.sum();
        out[3*n+a] = prob;
        cout << 3*n + a << setw(30) << prob << endl;
    }
       

   return out;    
}

double probability_rhombus_imp(Eigen::VectorXd init, double z, int n, std::vector<int> counts, std::vector<long> seqs){
    std::vector<double> z_counts;

    int size = counts.size();

    z_counts.resize(size); 
    cout << "in method " << endl;
    for (int k = 0; k<counts.size(); k++){
        z_counts[k] = pow(z, counts[k]);
    }
    cout << " generated z counts " << endl;
    Eigen::VectorXd vec = init; 

    for (int i = 1; i < (n+1)/2; i++){
        vec = multiply_z_matrix(seqs, z_counts,vec);
    }
    cout << " generated first half = " << vec.sum() << endl;
    init = multiply_z_matrix_c(n, seqs, z_counts, vec);
    vec = multiply_z_matrix(seqs, z_counts,vec);

    for (int j = 1; j <= n-(n+1)/2; j++){
        init = multiply_z_matrix(seqs, z_counts, init);
        vec = multiply_z_matrix(seqs, z_counts, vec);
    }
    
   return init.sum()/vec.sum();
}
/*
int main(int argc, char* argv[]){
    int n_end = 8;
    double z_end = 4;
    string name_n = std::to_string(n_end);
    ofstream n_output (string(" rhombus_kink_n= " + name_n +".txt").c_str());
    n_output << left << setw(5) << "n" << setw(30) << "z" << setw(30) << "prob" << endl;
    cout << left << setw(5) << "n" << setw(30) << "z" << setw(30) << "prob" << endl; 
    for (int n = 1 ; n <= n_end ; n++){
        std::vector<long> seqs = generate_linear_one_dim_sequences(2*n+1);
        std::vector<int> counts = generate_counts(seqs);
        for (double z = 0; z <= z_end; z+=0.02){
            Eigen::VectorXd init = generate_init(z,seqs, counts);
            Eigen::MatrixXd mat = generate_z_matrix_helper(seqs, z, counts);
            Eigen::MatrixXd mat_2 = generate_z_matrix_2_helper(n,mat,seqs);
            double prob_1 = probability_rhombus(n, mat, mat_2, init);
            cout << left << setw(5) << n  << setw(30) << z << setw(30) << setprecision(16) << prob_1 << endl; 
            n_output << left << setw(5) << n << setw(30) << z << setw(30) << setprecision(16) << prob_1 << endl; 
        }
    }
}
*/

int main(int argc, char* argv[]){
    int n_end = 8;
    double z_end = 4;
    for (double z = 3; z<=z_end; z+=0.25){ 
        string name_n = std::to_string(z);
        ofstream n_output (string("rhombus_perc_z = " + name_n +".txt").c_str());
        n_output << left << setw(5) << "n" << setw(5) << "a" << setw(30) << "z" << setw(30) << "prob_1" << endl;
        cout     << left << setw(5) << "n" << setw(5) << "a" << setw(30) << "z" << setw(30) << "prob_1" << endl;
        for (int n = 2; n <= n_end; n++){
            std::vector<long> seqs = generate_linear_one_dim_sequences(2*n+1);
            std::vector<int> counts = generate_counts(seqs);
           std::vector<double> ret = probability_rhombus_imp_omit_bulk(z,n,counts, seqs);
           for (int a = 0; a <= 4*n; a++){
                Eigen::VectorXd vec = generate_init(z,seqs, counts);
                double prob_1 = ret[a];
//                double prob_2 = probability_rhombus_imp_omit(a, z, n, counts, seqs);
                cout     << left << setw(5) << n << setw(5) << a << setw(30) << z << setw(30) << setprecision(16) << prob_1 << endl; 
                n_output << left << setw(5) << n << setw(5) << a << setw(30) << z << setw(30) << setprecision(16) << prob_1 << endl; 
            }
       }
    }
}
