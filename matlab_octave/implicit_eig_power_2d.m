%% Compute the eigenvalues for transfer matrix of width 1 through 21
eigenvalues = zeros(1, 6);
conv_rates = zeros(6, 60);
time = zeros(1,6);

for i=16:21
    tic();
    printf("On iteration %d \n", i);
    S = all_pairs_numrep(i);
    [e_val, progress] = implicit_eig_2d(S, eps);
    eigenvalues(i) = e_val;
    conv_rates(i,1:length(progress)) = progress;
    clear S
    elapsed_time = toc()
    time(i) = elapsed_time;
endfor

