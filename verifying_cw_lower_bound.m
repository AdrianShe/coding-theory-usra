format long

%% The case p = 2, q = 1
fprintf("The case p = 2, q = 1 \n")
t4 = eigs(generate_matrix(5))(1)
t2 = eigs(generate_matrix(3))(1)
bound = sqrt(t4/t2)

%% The case p = 2, q = 3
fprintf("The case p = 2, q = 3 \n")
t8 = eigs(generate_matrix(9))(1)
t6 = eigs(generate_matrix(7))(1)
bound = sqrt(t8/t6)

%% Testing other lower bounds
fprintf("Testing other lower bounds \n")
eigenvalues = zeros(15,1);
for i=1:15
  fprintf("Matrix %d \n", i + 1);
  fflush(stdout);
  eigenvalues(i) = eigs(generate_matrix(i+1))(1); %% t[i] in eigenvalue vector 
  %% is the dominant eigenvalue for a (i+1) x n configuration
endfor 
eigenvalues

M = zeros(5);

for p=1:5
   for q=1:5
      M(p,q) = (eigenvalues(p + 2 * q) / eigenvalues(2 * q))^(1/p);
   endfor
endfor

M(2,1)
M(2,3)
M
