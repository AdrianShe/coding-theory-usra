format long 

%% Transfer matrix T2
printf('Roots of T2 \n');
t2 = [1 -2 -6 0 1];
polyout(t2)
roots(t2)(1)

%% Transfer matrix T4
printf('Roots of T4 \n');
t4 = [-1 4 36 0 -105 15 64 -20 -4 1];
roots(t4)(1)
polyout(t4)

printf('True matrix \n');
M = generate_matrix(5);
polyout(poly(M))
roots(poly(M))(1)

%% Dual matrix D
printf('Matrix B6 \n');
B = [1 -12 3 24 2 -1];
polyout(B)
roots(B)(1)

