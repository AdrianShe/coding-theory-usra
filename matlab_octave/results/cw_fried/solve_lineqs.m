load friedland_eigenvalues

results_1 = zeros(2, 26);
for m=2:27
 A = [m 1; (m+1) 1];
 b = [log(friedland_eigenvalues(m-1)); log(friedland_eigenvalues(m))];
 results_1(:,m-1) = A \ b;
endfor 

results_2 = zeros(2, 26);
for m=2:27
 results_2(1,m-1) = (friedland_eigenvalues(m) / friedland_eigenvalues(m-1));
 results_2(2,m-1) = (friedland_eigenvalues(m-1)^(m+1) / friedland_eigenvalues(m)^(m));
endfor

exped_results = e .^ (results_1);

