%% Compute the eigenvalues for transfer matrix of width 1 through 21
eigenvalues = zeros(1, 10);
conv_rates = zeros(10, 60);
time = zeros(1,10);

for i=1:10
    tic();
    printf("On iteration %d \n", i);
    T = generate_ring_matrix_numrep(2 * i);
    [e_val, progress] = explicit_power(T, eps, ones(rows(T), 1));
    eigenvalues(i) = e_val;
    conv_rates(i,1:length(progress)) = progress;
    clear T
    elapsed_time = toc()
    time(i) = elapsed_time;
endfor

