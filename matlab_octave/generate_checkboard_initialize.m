%% Generate sequences
S = generate_sequences_numrep(n);
T = generate_sequences_numrep(n+1);

%% Set phase and generate corresponding matrices
left_pattern = generate_pattern(n, 0);
first = generate_edge_vec(S, left_pattern); 
left_compat_zero = generate_checkboard_compat(S, n, 0); 
left_compat_one = generate_checkboard_compat(S, n, 1);
M = generate_checkboard_matrix(S, left_compat_zero, left_compat_one);

%% Generate expander and right hand matrices
right_compat_zero = generate_checkboard_compat(T, n+1, 0);
right_compat_one = generate_checkboard_compat(T, n+1, 1);

if (mod(n, 2) == 0)
   zero_one_expander_matrix = generate_expander_checkboard_matrix(bitshift(S, 1) + 1, T, left_compat_zero, right_compat_one);
   one_zero_expander_matrix = generate_expander_checkboard_matrix(bitshift(S, 1), T, left_compat_one, right_compat_zero);
else
   zero_one_expander_matrix = generate_expander_checkboard_matrix(bitshift(S, 1), T, left_compat_zero, right_compat_one);
   one_zero_expander_matrix = generate_expander_checkboard_matrix(bitshift(S, 1) + 1, T, left_compat_one, right_compat_zero);
end

L = generate_checkboard_matrix(T, right_compat_zero, right_compat_one); 
right_pattern_zero = generate_pattern(n+1, 0); 
right_pattern_one = generate_pattern(n+1,1);
zero_right_indexes_zero = find(bitand(right_pattern_zero, T) != 0);
zero_right_indexes_one = find(bitand(right_pattern_one, T) != 0);
