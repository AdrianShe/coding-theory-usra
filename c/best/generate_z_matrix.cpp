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


using namespace std;
using namespace Eigen;

int digit_sum(long seq){
    int ret = 0;
    for (int i = 0; i < 32; i++){
       if ((seq >> i) % 2 == 1) ret++;
    }
    return ret;
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

Eigen::MatrixXd generate_z_matrix_helper(int length, std::vector<long> seqs, double z, std::vector<int> counts){
//    cout << " in helper " << endl;
    int size = seqs.size();
    std::vector<double> z_counts;
    z_counts.resize(size);
//    cout << counts.size() << endl;
    for (int k = 0; k<counts.size(); k++){
//        cout << " in loop k = " << k << endl;
//        cout << z_counts[k] << endl;
 //       cout << counts[k] << endl;
        z_counts[k] = pow(z, counts[k]);
    }
//    cout << " prepared count " << endl;
    Eigen::MatrixXd ret(size,size);
    ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
             if ((seqs[i] & seqs[j]) == 0){
                ret(i,j) = z_counts[i];
                ret(j,i) = z_counts[j];
             }   
        }
    }
    return ret;
}

Eigen::MatrixXd generate_z_matrix_expander_helper(int length, std::vector<long> seqs, std::vector<long> seqs_2, double z, std::vector<int> counts){
//    cout << " in helper " << endl;
    int size = seqs.size();
    int size_2 = seqs_2.size();
    std::vector<double> z_counts;
    z_counts.resize(size_2);
   for (int k = 0; k < size_2; k++){
       z_counts[k] = pow(z, counts[k]);
    }
//    cout << " prepared count " << endl;
    Eigen::MatrixXd ret(size_2,size);
    ret.fill(0);
    for (int i = 0; i < size_2; i++){
        for (int j = 0; j < size; j++){
             if ((seqs_2[i] & seqs[j]) == 0){
                ret(i,j) = z_counts[i];    
             }
        }       
    }
    return ret;
}

Eigen::MatrixXd generate_z_matrix_expander(int length, double z){
    std::vector<long> seqs = generate_linear_one_dim_sequences(length);
    std::vector<long> seqs_2 = generate_linear_one_dim_sequences(length+1);
    return generate_z_matrix_expander_helper(length, seqs,seqs_2, z, generate_counts(seqs_2));
}

Eigen::MatrixXd generate_z_matrix(int length, double z){
    std::vector<long> seqs = generate_linear_one_dim_sequences(length);
    return generate_z_matrix_helper(length,seqs ,z , generate_counts(seqs));
}

Eigen::MatrixXd generate_2z_matrix_helper(int length, std::vector<long> seqs, double z, std::vector<int> counts){
    int size = seqs.size();
    std::vector<double> z_counts;
    z_counts.resize(size);
    for (int k = 0; k<counts.size(); k++){
        z_counts[k] = pow(z, counts[k]);
    }
    Eigen::MatrixXd ret(size, size);
     ret.fill(0);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
             if ((seqs[i] & seqs[j]) == 0){
                ret(i,j) = z_counts[i]*counts[i];    
             }
        }       
    }
//    cout << ret << endl;
    return ret;
} 

Eigen::MatrixXd generate_2z_expander_matrix_helper(std::vector<long> seqs, std::vector<long> seqs_2, double z, std::vector<int> counts){  
    int size = seqs.size();
    int size_2 = seqs_2.size();
    std::vector<double> z_counts;
    z_counts.resize(size_2);
    for (int k = 0; k < counts.size(); k++){
        z_counts[k] = pow(z,counts[k]);
    }
    Eigen::MatrixXd ret(size_2, size);
    ret.fill(0);
    for (int i = 0; i < size_2; i++){
        for (int j = 0; j < size; j++){
             if ((seqs_2[i] & seqs[j]) == 0){
                ret(i,j) =counts[i]*z_counts[i];    
             }
        }       
    }
    return ret;
}

Eigen::MatrixXd generate_2z_matrix(int length, double z){
    std::vector<long> seqs = generate_linear_one_dim_sequences(length);
    return generate_2z_matrix_helper(length, seqs, z, generate_counts(seqs));
}

double compute_density_helper(int a, int b, int c, std::vector<long> seqs, std::vector<long> seqs_2, double z, std::vector<int> counts, std::vector<int> counts_2){        
    long double sum = 0;
    int cap = a*b+(a+1)*c;
    int size = seqs.size();
    Eigen::VectorXd init(size); 
    Eigen::VectorXd alt(size);
    for (int i = 0; i < size; i++){
        init(i) = pow(z, counts[i]);
        alt(i) = pow(z,counts[i]) * counts[i];
    }
    double max_z = pow(z,counts_2[counts_2.size()-1]);
    Eigen::VectorXd vec_new(size);
    vec_new << init;
    Eigen::MatrixXd S_a = 1/max_z*generate_2z_matrix_helper(a, seqs, z, counts);
    Eigen::MatrixXd T_a = 1/max_z*generate_z_matrix_helper(a, seqs, z, counts);
    Eigen::MatrixXd S_a1 = 1/max_z*generate_2z_matrix_helper(a+1, seqs_2, z, counts_2);
    Eigen::MatrixXd T_a1 = 1/max_z*generate_z_matrix_helper(a+1, seqs_2, z, counts_2);
    Eigen::MatrixXd E = 1/max_z*generate_z_matrix_expander_helper(a,seqs,seqs_2, z, counts_2);
    Eigen::MatrixXd E_S = 1/max_z*generate_2z_expander_matrix_helper(seqs,seqs_2,z,counts_2); 
  
    for (int k = 1; k <= b+c; k++){
        Eigen::VectorXd vec(size);    
        // 2 in initial column!!
        if (k == 1){
            vec << alt;
        } else{
            vec << init; 
        }
        // upto b columns
        for (int j = 2; j<=b; j++){
            if (j == k){
                vec = S_a*vec;
            } else {
                vec = T_a*vec; 
            }
        }
        // 2 in expander column!!
        if (k==b+1){
            vec = E_S*vec;
        } else{ 
            vec = E*vec;
        }
        // upto b+c columns
        for (int j = b+2; j<=b+c; j++){
            if (j ==  k){
                vec = S_a1*vec;
            }else {
                vec = T_a1*vec;
            }
        }
        sum+=vec.sum();
    }
        //compute mass
        for (int k =2; k <= b; k++){
            vec_new = T_a*vec_new;
        }
        vec_new=E*vec_new;
        for (int k = b+2; k <= b+c; k++){
            vec_new = T_a1*vec_new;
        }
        double denom = cap*vec_new.sum();
        return sum/denom;
}
                
                     
double brian_constant(int a , int b , int c, double z, std::vector<long> seqs, std::vector<long> seqs_2){
    int size = seqs.size();
    int size_2 = seqs_2.size();
    Eigen::VectorXd vec(size);
    std::vector<int> counts = generate_counts(seqs);
    for (int k = 0; k < size; k++){
       vec(k) = pow(z, counts[k]);
    }
    Eigen::VectorXd vec_t = vec;
    Eigen::VectorXd vec_b = vec;
    std::vector<int> counts_2 = generate_counts(seqs_2);
    Eigen::MatrixXd T_a =generate_z_matrix_helper(a, seqs, z, counts)*1/vec(size-1);
    Eigen::MatrixXd E_a = generate_z_matrix_expander_helper(a, seqs, seqs_2, z, counts_2)*1/vec(size-1);
    Eigen::MatrixXd T_a_1 = generate_z_matrix_helper(a+1, seqs_2, z, counts_2)*1/vec(size-1);   
    for (int i = 0; i < b -1; i++){
        vec_t = T_a*vec_t;
    }
    vec_b = T_a*vec_t;
    Eigen::VectorXd vec_b_new = E_a*vec_b;
    Eigen::VectorXd vec_t_new = E_a*vec_t;
    for (int i = 0; i < c-2; i++){
        vec_t_new = T_a_1*vec_t_new;
        vec_b_new = T_a_1*vec_b_new;
    }
    vec_t_new = T_a_1*vec_t_new;
  //  cout << "top = " << vec_t_new.sum() << endl;
  //  cout << "bot = " << vec_b_new.sum() << endl;
       return vec_t_new.sum()/vec_b_new.sum();
}

Eigen::VectorXd get_vec_a(Eigen::MatrixXd mat,std::vector<long> seqs,  std::vector<int> counts, Eigen::VectorXd vec, int a,int b, int c, double z){
    if (a==0){
        int fib_tb = fib (b+c+2); 
            int fib_t = fib(c+2);
            Eigen::VectorXd top(fib_t);
            Eigen::VectorXd bottom(fib_tb-fib_t);
            for (int k = 0; k < fib_t; k++){
                top(k) = pow(z, counts[k]);
             }
            bottom.fill(0);
            Eigen::VectorXd ret(fib_tb);
            ret << top, bottom;
           return ret; 
        }
    else return mat*vec;
 }

double andrew_constant (int a , int b , int c, double z, std::vector<long> seqs){
//    cout << "a = " << a << endl;//
//    cout << "b = " << b << endl;//
//    cout << "c = " << c << endl;//
  // Do original system
    int fib_t = fib(c+2);
    int fib_tb = fib (b+c+2);
    Eigen::VectorXd top(fib_t);
    Eigen::VectorXd bottom(fib_tb-fib_t);
    std::vector<int> counts = generate_counts(seqs);
    for (int k = 0; k < fib_t; k++){
        top(k) = pow(z, counts[k]);
    }
    bottom.fill(0);
    Eigen::MatrixXd T_bc = generate_z_matrix_helper(b+c, seqs, z, counts);   
    cout << "done matrix" << endl;
    Eigen::VectorXd vec(fib_tb);
    vec << top, bottom; 
    for (int l = 0; l < a; l++){
        cout << " a - l = " << a- l << endl;
        cout << "sum = " << vec.sum() << endl;
        vec = T_bc*vec;
    }
    cout << "done first multiplication" << endl;
    // Remove one square
    int fib_t_new = fib(c+1);
    Eigen::VectorXd top_new(fib_t_new);
    Eigen::VectorXd bottom_new(fib_tb-fib_t_new);
    for (int k = 0; k < fib_t_new; k++){
        cout << "a - k = " << a-k << endl;
        cout << "sum = " << vec.sum() << endl;
        top_new(k) = pow(z, counts[k]);
    }
    cout << "done second multiplication" << endl;
    bottom_new.fill(0);
    Eigen::VectorXd vec_new(fib_tb);
    vec_new << top_new, bottom_new;
    for (int l = 0; l < a; l++){
        vec_new = T_bc*vec_new;
    }
    // Return eta approx (?)

    return vec.sum()/vec_new.sum();
} 
    //Creates an instance of ofstream, and opens example.txt
   //    // Outputs to example.txt through a_file
    //      a_file<<"This text will now be inside of example.txt";
    //        // Close the file stream explicitly
    //          a_file.close();}
//method to compute density of L_shape
int main(int argc, char* argv[]){
    int a_end = atoi(argv[1]);
    int b_end = atoi(argv[2]);
    int c_end = atoi(argv[3]);
    double z_end = atof(argv[4]);
    for (int a = 1; a <=a_end; a++){
        string name = std::to_string(a);
        ofstream output (string("density_a="+name+".txt").c_str());
        output << left << setw(5) << "a" <<  setw(5) <<"b" <<  setw(5) << "c" << setw(5) << "z" << setw(30) << "density" << endl; 
        std::vector<long> seqs = generate_linear_one_dim_sequences(a);
        std::vector<long> seqs_2 = generate_linear_one_dim_sequences(a+1);
        std::vector<int> counts = generate_counts(seqs);
        std::vector<int> counts_2 = generate_counts(seqs_2);
        for (int b = 1; b<=b_end; b++){
            for (int c = 2; c<=c_end; c++){
                for (double z = 0.5; z<=z_end; z*=2){
                    double density =  compute_density_helper(a, b, c, seqs, seqs_2, z, counts,counts_2);
                    cout << setprecision(18) << left << setw(5) << a << setw(5) << b << setw(5) << c << setw(5) << z << setw(30) << density << endl;
                    output << setprecision(18) << left << setw(5) << a << setw(5) << b << setw(5) << c << setw(5) << z << setw(30) << density <<endl;
                }
             }
        }
    }
}

/* METHODS TO COMPUTE DENSITY OF SQUARE
int main(int argc, char* argv[]){
    int length = atoi(argv[1]);
    double z_end = atof(argv[2]);
    ofstream output ( "2.txt" );
    output << left << setw(5) << "area" << setw(5) << "z"<< setw(30) << "moment" << setw(30) << "density" << endl;
 
    for (int z = 0; z <=z_end; z++){
        long double sum = 0;
        std::vector<long> seqs = generate_linear_one_dim_sequences(length);
        std::vector<int> counts = generate_counts(seqs); 
        int fib_tb = fib(length+2);
        Eigen::VectorXd vec(fib_tb);
        Eigen::VectorXd init(fib_tb); 
        Eigen::VectorXd alt(fib_tb);
        for (int i = 0; i < fib_tb; i++){
            init(i) = pow(z, counts[i]);
            alt(i) = pow(z,counts[i]) * counts[i];
        }
        Eigen::VectorXd vec_new(fib_tb);
        vec_new << init;
        Eigen::MatrixXd S = generate_2z_matrix_helper(length, seqs, z, counts);
        Eigen::MatrixXd T = generate_z_matrix_helper(length, seqs, z, counts);
        for (int k = 1; k < length; k++){
            vec << init;
            vec_new = T*vec_new;
            alt = T*alt;
            for (int j = 1; j < k; j++){
                vec = T*vec;
            }
            vec = S*vec;
            for (int l = 1; l < length-k; l++){
                vec = T*vec;
            }
            sum+=vec.sum(); 
        }
        sum+=alt.sum();
        output << setprecision(16) << left << setw(5) <<  length*length << setw(5) << z << setw(30) << sum << setw(30) << sum/vec_new.sum()<< endl;
        cout << setprecision(16) << left << setw(5) <<  length*length << setw(5) << z << setw(30) << sum << setw(30) <<  sum/vec_new.sum()<< endl;
 
    }
    
    output.close();
}
*/

/* METHODS TO COMPUTE ANDREW AND BRIAN CONSTANT
int main(int argc, char* argv[]) {
    ofstream output ( "out.txt" );
    output << left << setw(5) << "a" << setw(5) << "b" << setw(5) <<"c" << setw(5) << "z"<< setw(18) << "entropy"  << endl;
 
//    int a_end = atoi(argv[1]);
    int b_end = atoi(argv[2]);
    int c_end = atoi(argv[3]);
       double z = atof(argv[4]);
    for (int a = 16; a <= a_end; a++){
               std::vector<long> seqs = generate_linear_one_dim_sequences(a);
               std::vector<long> seqs_2 = generate_linear_one_dim_sequences(a+1);
       for (int b = 35; b <= b_end; b++){
            for (int c = 35; c <= c_end; c++){ 
                double ret = brian_constant(a,b,c,z,seqs, seqs_2);
                cout<< setprecision(16) << left << setw(5) <<  a << setw(5) << b << setw(5) << c << setw(5) << z << setw(18) << ret << endl;
                output << setprecision(16) << left << setw(5) <<  a << setw(5) << b << setw(5) << c << setw(5) << z << setw(18) << ret << endl;
                }
            }
        }
 
    int a_end = atoi(argv[1]);
    int bc_end = atoi(argv[2]);
    double z = atof(argv[3]);
    int c;
    double ret;
//    for (int bc=16; bc<=bc_end; bc++){
        std::vector<long> seqs = generate_linear_one_dim_sequences(bc);
        cout << "done sequences" << endl;
        for (int b = 1; b <= bc-2; b++){
            c = bc - b;
            for (int a = 35; a <= a_end; a++){
                ret = andrew_constant(a,b,c,z,seqs);
                cout<< setprecision(16) << left << setw(5) <<  a << setw(5) << b << setw(5) << c << setw(5) << z << setw(18) << ret << endl;
                output << setprecision(16) << left << setw(5) <<  a << setw(5) << b << setw(5) << c << setw(5) << z << setw(18) << ret << endl;
                }
            }
        }
//
    for (int bc = 3 ; bc<=bc_end; bc++){
        std::vector<long> seqs = generate_linear_one_dim_sequences(bc);
        std::vector<int> counts = generate_counts(seqs);
        Eigen::VectorXd top(seqs.size());
        Eigen::VectorXd bot(seqs.size());
        Eigen::MatrixXd mat =1/pow(z,counts[seqs.size()-1])*generate_z_matrix_helper(bc, seqs, z, counts);
        for (int b = 1; b <= bc-2; b++){
            c = bc - b;
            for (int a = 0; a <= a_end; a++){
               top = get_vec_a(mat,seqs,counts,top, a, b,  c, z);
               cout << top.sum()<< endl;
               bot = get_vec_a(mat,seqs,counts,bot,a,b+1,c-1,z);
               cout << bot.sum() << endl;
               ret = top.sum()/bot.sum();
               cout<< setprecision(16) << left << setw(5) <<  a << setw(5) << b << setw(5) << c << setw(5) << z << setw(18) << ret << endl;
               output << setprecision(16) << left << setw(5) <<  a << setw(5) << b << setw(5) << c << setw(5) << z << setw(18) << ret << endl;
            } 
        }
    }

    output.close();
 }
*/
