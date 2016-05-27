format long

upper_bound = zeros(1,8);
for i=2:2:16
    printf("Matrix of size %d \n", i);
    fflush(stdout);
    %% Find eigenvalue of ring matrix
    eig = eigs(generate_ring_matrix(i))(1);
    upper_bound(i/2) = eig;
endfor 

upper_bound

capacities = zeros(1,8);
for i=1:8
    capacities(i) = upper_bound(i)^(1 / (2 * i));
endfor 

capacities    
