function [val] = compute_partition_function(N, z, S, C)
    %% Compute the partition function Z_N(z) for some N, z
    %% N: Size of matrix
    %% z: weight
    %% S: list of sequences
    %% C: counter object for S
   
    init_vec = zeros(length(C), 1);
    for i=1:length(init_vec)
       init_vec(i) = z^(C(i));
    endfor

    M = generate_z_matrix(z, S,C);

    final_vec = M^(N-1) * init_vec; 
    val = sum(final_vec);
end
  
