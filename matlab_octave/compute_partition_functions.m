function [vals] = compute_partition_functions(s, weights)
 %% s: length of sequences
 %% weights: sequence of weights 
vals = zeros(1, length(weights));
S = generate_sequences_numrep(s);
C = counter(S);
%power = 1/s^2;

for i=1:length(weights)
  val = compute_partition_function(s, weights(i), S, C);
  vals(i) = val;
  fprintf('%d %f \n', s, weights(i));
  if (mod(i, 100) == 0)
	 save temp_truncated vals
  endif
  fflush(stdout); 
endfor
end
