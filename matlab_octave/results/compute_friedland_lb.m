load upper_bound_eigs
friedland = zeros(4,9);
for i=2:5
 for j=1:9
  if (i + 2 * j <= 20)
   friedland(i-1,j) = (upper_bound_eigs(i + 2 * j) / upper_bound_eigs(2 * j))^(1 / i);
  endif
 endfor
endfor

friedland(1,:)'
friedland(2,:)'
friedland(3,:)'
