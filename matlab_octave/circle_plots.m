plot(-10:0.05:10, cylinder_approx_rho(1:2:9,:)); title('Cylinder Rho Approximation EVEN n'); xlabel('log z'); ylabel('log rho'); legend('n=6', 'n=8', 'n=10', 'n=12', 'n=14', 'location', 'northwest')

plot(-10:0.05:10, cylinder_approx_rho(2:2:9,:)); title('Cylinder Rho Approximation ODD n'); xlabel('log z'); ylabel('log rho'); legend('n=7', 'n=9', 'n=11', 'n=13', 'location', 'northwest')

plot(-10:0.05:10, torus_approx_rho(1:2:9,:)); title('Torus Rho Approximation EVEN n'); xlabel('log z'); ylabel('log rho'); legend('n=6', 'n=8', 'n=10', 'n=12', 'n=14', 'location', 'northwest') figure;

plot(-10:0.05:10, torus_approx_rho(2:2:9,:)); title('Torus Rho Approximation ODD n'); xlabel('log z'); ylabel('log rho'); legend('n=7', 'n=9', 'n=11', 'n=13', 'location', 'northwest')

plot(-10:0.05:10, approx_rho_free(8,:), -10:0.05:10, cylinder_approx_rho(8,:), -10:0.05:10, torus_approx_rho(8,:), -10:0.05:10, approx_rho_1(8,:)); title('Rho approximation for N=13'); xlabel('log z'); ylabel('log rho'); legend('Free', 'Cylinder', 'Torus', 'Checkboard', 'location', 'northwest')
