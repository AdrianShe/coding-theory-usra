%% moments{i,j,k}(m,n) denotes the (k-1)^th moment of width i+1
%% of weight weights(j) on an b x c grid

weights = [-10:0.1:10];
weights = 2 .^ weights; 
sizes = 2:3;
b = 1:20;
c = 1:20;
moments = cell(length(sizes), length(weights), 3); 

for i=1:length(sizes)
  for j=1:length(weights)
    for k=1:3
     moments{i,j, k} = zeros(length(b), length(c));
    end
  end
end

S = generate_sequences_numrep(2);
C = counter(S); 
A_smaller = generate_auxiliary_matrix(S, C, S, C); 

for i=1:length(sizes)
   printf('Generating sequences %d \n', i);
   T = generate_sequences_numrep(sizes(i) + 1); 
   D = counter(T); 
   A_expander = generate_auxiliary_matrix(S, C, T, D);
   A_larger = generate_auxiliary_matrix(T, D, T, D);
   
   for j=1:length(weights) 
     [M, v] = generate_moment_matrix(weights(j), A_smaller, C);
     E = generate_moment_matrix(weights(j), A_expander, [0]);
     N = generate_moment_matrix(weights(j), A_larger, [0]); 
     result_matrix = zeros(length(b), length(c)); 
     for k=1:length(b)
        for l=1:length(c)
          	printf('%d %d %d %f \n', sizes(i), b(k), c(l), weights(j));
      		result = compute_moments_l(M, E, N, b(k), c(l), v); 
                moments{i,j,1}(k,l) = result(1); 
                moments{i,j,2}(k,l) = result(2);
                moments{i,j,3}(k,l) = result(3);  
   		fflush(stdout);
   	end
     end
   end

   S = T; 
   C = D; 
   A_smaller = A_larger;
end
