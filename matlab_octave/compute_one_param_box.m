function [ratio] = compute_one_param_box(n, option)
    bulk = floor(sqrt(n)); %% Associate n with its dimensions
    l = n - bulk^2;
    if (l >= bulk + 1)
      side = bulk + 1;
      bottom = l - bulk - 1;
    else 
      side = l;
      bottom = 0;
    end

    S = generate_sequences_numrep(bulk);
    C = counter(S);
    A = generate_auxiliary_matrix(S, C, S, C);
    T1 = generate_z_matrix(10, A); 
    init = (10 .^ C') / (10 ^ max(C));

    if (side == 0)
	if (option == 'o')
  	   init_zero = (10 .^ C') / (10 ^ max(C));
  	   init_zero(S >= 2^(bulk -1)) = 0;
           init = T1 ^ (bulk - 1) * init; 
  	   init_zero = T1 ^ (bulk - 1) * init_zero;
           ratio = sum(init) / sum(init_zero);
	end

        if (option == 'n')
	   init = T1 ^ (bulk - 1) * init;
           init_zero = init(mod(S, 2) == 0);
           ratio = sum(init) / sum(init_zero);
        end 


    elseif (side < bulk)
        T = generate_sequences_numrep(side);
        T_new = bitshift(T, bulk - side); 
        D = counter(T);
        A = generate_auxiliary_matrix(S, C, T_new, D);
        T2 = generate_z_matrix(10, A); 

	if (option == 'o')
  	   init_zero = (10 .^ C') / (10 ^ max(C));
  	   init_zero(S >= 2^(bulk -1)) = 0;
           init = T2 * T1 ^ (bulk - 1) * init; 
  	   init_zero = T2 * T1 ^ (bulk - 1) * init_zero;
           ratio = sum(init) / sum(init_zero);
        end

	    if (option == 'n')
	         init = T2 * T1 ^ (bulk - 1) * init;
           init_zero = init(mod(T, 2) == 0);
           ratio = sum(init) / sum(init_zero);
        end 

    elseif (side == bulk)
	if (option == 'o')
  	   init_zero = (10 .^ C') / (10 ^ max(C));
  	   init_zero(S >= 2^(bulk -1)) = 0;
           init = T1 ^ bulk * init; 
  	   init_zero = T1 ^ bulk * init_zero;
           ratio = sum(init) / sum(init_zero);
	end

        if (option == 'n')
	   init = T1 ^ bulk * init;
           init_zero = init(mod(S, 2) == 0);
           ratio = sum(init) / sum(init_zero);
        end 
    else
 	T = generate_sequences_numrep(bulk + 1);
        S_new = bitshift(S, 1);
        D = counter(T);
        A = generate_auxiliary_matrix(S_new, C, T, D); 
	E = generate_z_matrix(10, A);
        A = generate_auxiliary_matrix(T, D, T, D);
        T2 = generate_z_matrix(10, A);
	
	if (option == 'o') 
	   init_zero = (10 .^ C') / (10 ^ max(C));
  	   init_zero(S >= 2^(bulk -1)) = 0;
           init = T2 ^ bottom * E *  T1 ^ (bulk - bottom - 1) * init; 
  	   init_zero = T2 ^ bottom * E  * T1 ^ (bulk - bottom - 1) * init_zero;
           ratio = sum(init) / sum(init_zero);
        end
        if (option == 'n')
	   ratio = brians_constant(T1, T2, E, init, bulk - bottom , bottom + 1);
 	end

    end
      % sum(init)
 %  sum(init_zero)
 ratio
end
