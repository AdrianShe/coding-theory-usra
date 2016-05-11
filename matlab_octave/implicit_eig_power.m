%% Compute the eigenvalues for transfer matrix of width 1 through 22
eigenvalues = zeros(1, 20);
conv_rates = zeros(20, 60);

for i=16:20
    printf("On iteration %d \n", i);
    S = generate_sequences_numrep(i);
    [eval, progress] = implicit_eig_1d(S, eps);
    eigenvalues(i) = eval;
    conv_rates(i,1:length(progress)) = progress;
    clear S
endfor

