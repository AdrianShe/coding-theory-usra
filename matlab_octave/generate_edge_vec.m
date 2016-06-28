function [edge] = generate_edge_vec(S, hidden)
   edge = ones(length(S), 1);
   hidden_vec = bitand(S, hidden);
   edge(find(hidden_vec != 0)) = 0;
end
