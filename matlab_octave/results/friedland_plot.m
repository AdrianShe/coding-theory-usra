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
  differences(i) = data(i+1) - data(i);
endfor 

figure;
plot(1:26, differences, '*');
title('Plot of Successive Differences')
xlabel('i')
ylabel('Successive Differences in Lambda_i/eta^i')

figure;
plot(1:26, log10(abs(differences)), '*');
title('Plot of Log10(Successive Differences)')
xlabel('i')
ylabel('Log of Successive Differences in Lambda_i/eta^i')

lim = 1.069354538769;
differences_lim = zeros(1,27);
for i=1:27
  differences_lim(i) = data(i) - lim;
endfor

figure
plot(2:28, log10(abs(differences_lim)), '*');
title('Plot of Distances from Conjectured Limit = 1.069354538769')
xlabel('i')
ylabel('Difference from Limit')
