pkg load symbolic

warning('off', 'all');

syms x

T2 = generate_matrix(3)
factor(poly2sym(poly(T2)))

T4 = generate_matrix(5)
factor(poly2sym(poly(T4)))

B6 = generate_ring_matrix(6)
factor(poly2sym(poly(B6)))
