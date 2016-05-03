%% Construct matrix for recursion
A = [1 1 1 1 1; 1 0 1 1 1; 1 1 0 0 1; 1 1 0 0 0; 1 1 1 0 0];

%% Compute first few terms in sequence
%% of number of 3 x n matrices with no
%% adjacent ones in rows or columns
vec = [1; 1; 1; 1; 1];
count = zeros(20, 1);
count(1) = sum(vec);

for i=2:20
    vec = A * vec;
    count(i) = sum(vec);
endfor

fprintf("Number of 3 x n matrices with no adjacent ones in rows or columns \n")
format long;
count 

fprintf("Estimate of Theoretical Capacity \n");
log2(3.63138126040364)

fprintf("Emperical Capacity \n");
polyfit((1:20)', log2(count), 1)(1)
