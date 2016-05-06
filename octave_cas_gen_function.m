pkg load symbolic
T = generate_matrix(3) %% Generate transfer matrix

syms x
M = eye(5) - x * T;

printf('Generating the generating function \n');
fflush(stdout)
inverse = inv(M);
column_sum = sum(inverse);
all_sum = sum(column_sum);
gen_function = simplify(all_sum)

%% Creating power series of function based on 
%% derivatives
printf('Creating first few terms of the power series \n');
fflush(stdout)
coefficients = zeros(9,1);
coefficients(1) = function_handle(gen_function)(0);
cur = gen_function;
for i=1:8
    cur = diff(cur);
    coefficients(i+1) = function_handle(cur)(0) / factorial(i);
endfor
coefficients'


