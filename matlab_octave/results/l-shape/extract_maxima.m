converged = cell(9, 20);

for i=2:10
 if (mod(i,2) == 0) 
   for j=1:20
    converged{i - 1, j} = plot_results(probabilities, i, j, 2:2:20);
   end
 else
   for j=2:20
    converged{i - 1, j} = plot_results(probabilities, i, 2:2:20, j);
   end
 end
end

maxima = cell(9, 1)
for i=2:10
  if (mod(i,2) == 0)
    maxima_matrix = zeros(20, 10)
    for j=1:20
      find_maxima = max(converged{i-1, j}');
      for k=1:10
         maxima_matrix(j, k) = find(converged{i-1,j}(k,:) == find_maxima(k));
      end
    end
  else
    maxima_matrix = zeros(19, 10)
    for j=2:20
      find_maxima = max(converged{i-1, j}');
      for k=1:10
         maxima_matrix(j - 1, k) = find(converged{i-1,j}(k,:) == find_maxima(k));
      end
    end
  end
  maxima{i-1} = maxima_matrix
end

