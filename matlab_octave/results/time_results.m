format long;
load explicit_res
load oned_implicit_res
load twod_implicit_res

printf('Linear Regression Result for Explicit Representation of Matrix \n')
res = polyfit((1:20)', log(time_explicit(1:20)), 1)
exp(res(1))

printf('Linear Regression Result for Implicit Pairs \n')
res = polyfit((1:18)', log(time_pairs(1:18)), 1)
exp(res(1))

printf('Linear Regression Result for Implicit Sequences \n')
res = polyfit((1:17)', log(time(1:17)), 1)
exp(res(1))

%% Make plot on common part
figure
plot(1:20, log(time_explicit(1:20)), 'b')

hold on
plot(1:18, log(time_pairs(1:18)), 'r')

hold on
plot(1:17, log(time(1:17)), 'g')


title('Log(run time) for eigenvalue calculation algorithms v. Size')
xlabel('Size of Input')
ylabel('Log(run time)')
h = legend('Explicit Matrix', 'Pairs of Sequences', 'Single Sequence');
legend(h, 'location', 'northwest');
