%% Compute the eigenvalues for transfer matrix of width 1 through 21
eigenvalues = zeros(1, 21);
conv_rates = zeros(21, 60);
time = zeros(1,21);

for i=1:21
    tic();
    printf("On iteration %d \n", i);
    S = generate_sequences_numrep(i);
    [e_val, progress] = implicit_eig_1d(S, eps);
    eigenvalues(i) = e_val;
    conv_rates(i,1:length(progress)) = progress;
    clear S
    elapsed_time = toc()
    time(i) = elapsed_time;
endfor

