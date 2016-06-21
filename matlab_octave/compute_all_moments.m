weights = [-1:0.001:10];
weights = 2 .^ weights; 
sizes = 2:15
moments = cell(length(sizes), 1)

for i=1:length(sizes)
  moments{i} = zeros(3, length(weights));
end

for i=1:length(sizes)
   for j=1:length(weights) 
     printf("%d %f \n", sizes(i), weights(j));
     moments{i}(:,j) = compute_moments(weights(j), sizes(i), sizes(i)); 
     fflush(stdout);
   end
end
