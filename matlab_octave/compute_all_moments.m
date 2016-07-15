weights = [-10:0.01:10];
weights = 2 .^ weights; 
sizes = 2:15;
moments = cell(length(sizes), 1);

for i=1:length(sizes)
  moments{i} = zeros(3, length(weights));
end

for i=1:length(sizes)
   printf('Generating sequences %d \n', i);
   S = generate_sequences_numrep(sizes(i)); 
   C = counter(S); 
   A = generate_auxiliary_matrix(S, C, S, C);
   for j=1:length(weights) 
     printf('%d %f \n', sizes(i), weights(j));
     moments{i}(:,j) = compute_moments(weights(j), A, C, sizes(i)); 
     fflush(stdout);
     %% if (mod(j,100) == 0)
      %%  save try_this.txt moments
     %% end
   end
   save moments_finer.txt moments
end
