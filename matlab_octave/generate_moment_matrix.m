function [M, v] = generate_moment_matrix(z, A, C)
   %% Generate column-to-column transfer matrix
   %% weighting the presence of 1s
   %% z: weight
   %% A: auxiliary matrix of sequence compitability
   %% C: counter object of C
   %% M: cell array with original matrix, and first/second moments
   %% v: cell array with initial states for vector v

   M = cell(3,1);
   v = cell(3,1);

   for i=1:3
      M{i} = zeros(length(C));
      v{i} = zeros(length(C), 1);
   endfor 

  %% Generate initial matrices 
  M{1} = z .^ A;
  M{2} = A  .* (z .^ (A - 1));
  M{3} = ((A .* (A - 1)) ./ 2) .* (z .^ (A - 2));


  %% Generate initial vectors
  C = C';
  v{1} = z .^ C; %% Zeroth moment vector 
  v{2} = C .* (z .^ (C - 1)); %% n * z^(n-1): first moment vector
  v{3} = ((C .* (C-1)) ./ 2) .* (z .^ (C-2)); %% n(n-1)/2 * z^(n-2): second moment
end 
   
