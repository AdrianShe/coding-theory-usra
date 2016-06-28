%% Compute the eigenvalues for transfer matrix of width 1 through 21
eigenvalues = zeros(1, 21);
conv_rates = zeros(21, 60);
time = zeros(1,21);

for i=1:21
    tic();
    printf("On iteration %d \n", i);
    S = all_pairs_numrep(i);
    T = build_matrix_from_pairs(S); 
    [e_val, progress] = explicit_power(T, eps, ones(rows(T), 1));
    eigenvalues(i) = e_val;
    conv_rates(i,1:length(progress)) = progress;
    clear S
    clear T
    elapsed_time = toc()
    time(i) = elapsed_time;
endfor

