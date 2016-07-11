%% Using matricies calculated explicit, determine
%% matrix of lower bounds

load explicit_res

lbs = zeros(8);

for p=2:9
   for q=1:8
     if (p + 2 * q < 20)
          lbs(p-1, q) = compute_lb(eigenvalues,p,q);
     endif
    endfor
endfor
