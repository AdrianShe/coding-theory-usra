function [moments] = compute_square_moments(a,p,z, enforce_same = false)
  %% a, b: ranges of dimensions of square
  %% z: range of z
  %% p: initial phase at top left corner

  moments = cell(length(a),1);

  for i=1:length(a)
     S = generate_sequences_numrep(a(i));
     C = counter(S);
     A = generate_auxiliary_matrix(S,C,S,C);
     results = zeros(3, length(z));
     [top, bottom, left, right] = generate_square_patterns(a(i),a(i),p);
     for j=1:length(z)
	[M, v] = generate_moment_matrix(z(j), A, C);   
        if (!enforce_same)  
		results(:,j) = compute_checkboard_square_moments(a(i), a(i), S, M, v, top, bottom, left, right); 
        else
		results(:,j) = compute_checkboard_square_moments(a(i), a(i), S, M, v, top, top, left, left); 
        end
        fprintf('%d %f \n', a(i), z(j));
        fflush(stdout);
     end
     moments{i} = results;
    % save checkboard_new_results.txt moments
end
