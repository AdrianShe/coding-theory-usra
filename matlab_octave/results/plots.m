load explicit_res
eta = 1.50304808247533 
data = zeros(1,20)

for i=1:20
  data(i) = eigenvalues(i) / eta^i
endfor

figure;
plot(1:20, data, '*');
title('Plot of n v. Lambda_i/eta^i')
xlabel('n')
ylabel('Lambda_i/eta^i')


figure;
plot(log(1:20), log(data), '*');
title('Plot of log(n) v. log(Lambda_i/eta^i)')
xlabel('log(n)')
ylabel('log(Lambda_i/eta^i)')


