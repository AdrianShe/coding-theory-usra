function [lb] = compute_lb(vec,p,q)
    lb = nthroot(vec(p + 2 * q + 1) / vec(2 * q + 1), p);
end
