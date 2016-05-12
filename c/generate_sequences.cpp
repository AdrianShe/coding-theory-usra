#include <iostream>
#include <cstdlib>
#include <vector>
#include <Eigen/Dense>
#include "generate.h"

using namespace std;

vector<long> generate_sequences(int length) {
    // Create the array of sequences 
   vector< vector<long> > temp;
    
    // Initialize the array
    vector<long> init;
    init.push_back(0);   
    temp.push_back(init);
    init.push_back(1);
    temp.push_back(init);
      
    // Now iterate
    for (int i = 2; i <= length; i++) {
        vector<long> all;
        vector<long> end_in_zero = temp[i-1];
        vector<long> end_in_one = temp[i-2];

        for (int j = 0; j < end_in_zero.size(); j++) {
          end_in_zero[j] = end_in_zero[j] << 1; // Generate sequences ending in zero
        }

        for (int j = 0; j < end_in_one.size(); j++) {
          end_in_one[j] = (end_in_one[j] << 2) + 1; // Generate sequences ending in one
        }
        all.insert(all.end(), end_in_zero.begin(), end_in_zero.end());
        all.insert(all.end(), end_in_one.begin(), end_in_one.end());
        temp.push_back(all);
        // cout << "Size " << all.size() << endl;
        // cout << "Size of array " << temp.size() << endl; 
    }
    return temp[length];
}

int main(int argc, char* argv[]) {
    vector <long> sequences = generate_sequences(atoi(argv[1]));
    for (int i = 0; i < sequences.size(); i++) {
        cout << sequences[i] << endl;
    }
}
