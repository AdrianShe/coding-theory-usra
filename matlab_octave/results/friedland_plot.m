load friedland_eigenvalues
eta = 1.50304808247533 
data = zeros(1,27);

for i=2:28
  data(i-1) = friedland_eigenvalues(i-1) / eta^i;
endfor

figure;
plot(2:28, data, '*');
title('Plot of i v. Lambda_i/eta^i Using Friedland')
xlabel('i')
ylabel('Lambda_i/eta^i')

differences = zeros(1,26);
for i=1:26
  differences(i) = abs(data(i+1) - data(i));
endfor 

figure;
plot(1:26, differences, '*');
title('i v. Lambda_(i+1)/eta^(i+1) - Lambda_i/eta^i')
xlabel('i')
ylabel('Successive Differences in Lambda_i/eta^i')

figure;
plot(1:26, log10(differences), '*');
title('i v. log(Lambda_(i+1)/eta^(i+1) - Lambda_i/eta^i)')
xlabel('i')
ylabel('Log of Successive Differences in Lambda_i/eta^i')


