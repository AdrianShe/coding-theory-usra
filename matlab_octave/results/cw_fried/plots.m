load explicit_res
eta = 1.50304808247533 
data = zeros(1,20);

for i=1:20
  data(i) = eigenvalues(i) / eta^i;
endfor

figure;
plot(1:20, data, '*');
title('Plot of i v. Lambda_i/eta^i')
xlabel('i')
ylabel('Lambda_i/eta^i')

differences = zeros(1,19);
for i=1:19
  differences(i) = data(i+1) - data(i);
endfor 

figure;
plot(1:19, differences, '*');
title('i v. Lambda_(i+1)/eta^(i+1) - Lambda_i/eta^i')
xlabel('i')
ylabel('Successive Differences in Lambda_i/eta^i')

figure;
plot(1:19, log(differences), '*');
title('i v. log(Lambda_(i+1)/eta^(i+1) - Lambda_i/eta^i)')
xlabel('i')
ylabel('Log of Successive Differences in Lambda_i/eta^i')


