%% Construct matrix for recursion
A = [1 1 1 1 1; 1 0 1 1 1; 1 1 0 0 1; 1 1 0 0 0; 1 1 1 0 0];

guess = [1;1;1;1;1];
guess = guess/norm(guess);
eigen = zeros(20,1);
guess_t = guess.';
guess = A * guess;
eigen(1) = guess_t * guess; 

for j=2:20
    I = eye(5);
    B = eigen(j-1)*I;
    C = A-B;
    guess = linsolve(C,guess, struct());
    guess = guess/norm(guess);
  %%  fprintf('eigenvector estimate \n')
   %% guess
    guess_t = guess.';
    guess = A * guess;
    eigen(j) = guess_t * guess;
   %% fprintf('eigenvalue estimate \n')
   %% eigen(j)
endfor
    fprintf('eigenvalue estimates \n')
    format long;
    eigen