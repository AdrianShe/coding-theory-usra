error = zeros(4000, 2);
for a=1:10
  for b=1:20
    for c=1:20
      idx = (a-1) * 400 + 20 * (b-1) + c;
      error(idx, 1) = abs(free_results{a}(b,c) - best);
      error(idx, 2) = a * b + (a+1) * c;
    end
   end
end
