%% Construct the matrix A representing the recursion
A = [1 1 1; 1 0 1; 1 1 0];

%% Compute C_n: the number of 2 x n matrices
%% with no adjacent ones in each row or each column
vec = [1; 1; 1];
count = zeros(10, 1);
count(1) = sum(vec);

for i=2:20
    vec = A * vec;
    count(i) = sum(vec);
endfor

fprintf('Number of 2 x n matrices with no adjacent ones \n');
count
fprintf('Theoretical Capacity \n');
log2(1+sqrt(2)) %% Theoretical Capacity
fprintf('Emperically Determined Capacity \n');
polyfit((1:20)', log2(count), 1)(1) %% Emperically determined capacity

