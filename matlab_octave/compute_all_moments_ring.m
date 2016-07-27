weights = [-10:0.05:10];
weights = 2 .^ weights; 
sizes = 2:16;
moments = cell(length(sizes), 1);

for i=1:length(sizes)
  moments{i} = zeros(3, length(weights));
end

for i=1:length(sizes)
   printf('Generating sequences %d \n', i);
   S = generate_ring_sequences_numrep(sizes(i)); 
   C = counter(S); 
   A = generate_auxiliary_matrix(S, C, S, C);
   for j=1:length(weights) 
     printf('%d %f \n', sizes(i), weights(j));
     moments{i}(:,j) = compute_moments(weights(j), A, C, sizes(i)); 
     fflush(stdout);
   end
end
