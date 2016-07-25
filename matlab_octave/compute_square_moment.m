function [moments] = compute_square_moments(a,b,p,z)
  %% a, b: ranges of dimensions of square
  %% z: range of z
  %% p: initial phase at top left corner

  moments = cell(a,z)

  for i=1:length(a)
     S = generate_sequences_numrep(a);
     C = counter(S);
     A = generate_auxiliary_matrix(S,C,S,C);

     for j=1:length(z)
	[M, v] = generate_moment_matrix(z, A, C);     
        results = zeros(3, length(b));
        for k=1:length(b) 
      	   [top, bottom, left, right] = generate_square_patterns(a(i),b(k),p);
	   results(:,k) = compute_checkboard_square_moments(a, b(k), S, M, v, top, bottom, left, right); 
	 end
        fprintf('%d %d %f \n', a(i), b(k), z(j))
        moments{i,j} = results;
     end
end
