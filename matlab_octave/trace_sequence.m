function [sequence] = trace_sequence(M, p,  q)
  %% Test if sequence of trace ratios is monotonic
  %% M: the matrix
  %% p: root to be taken
  %% q: length of sequence
  trace = @(M) sum(diag(M));
  sequence = zeros(1, q);
  for i=1:q
     sequence(i) = trace(M ^ (p + 2 * i)) / trace(M ^ (2 * i));
  endfor
end
