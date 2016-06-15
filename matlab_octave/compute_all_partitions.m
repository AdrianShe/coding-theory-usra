weights = [0:0.01:4];
part_function_results = zeros(19, length(weights));

for s=2:20
   printf('Number %d \n', s);
   fflush(stdout);
   part_function_results(s-1,:) = compute_partition_functions(s, weights);
   save partition_function_values_truncated part_function_results
endfor

%plot(weights, part_function_results);
