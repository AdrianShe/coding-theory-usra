%% Produce local approximation of sufrace press and energy energy
%% from finite dimensional system.

%load 2_16_-10_10_hundredth_moments.txt
%load checkboard_moments.txt
approx_a_4 = zeros(7, 401);
approx_kappa_4 = zeros(7, 401);
approx_rho_4 = zeros(7, 401);
moment = checkboard_1

for n=10:16
	matrix = [1 n^2 n; 1 (n-4)^2 n-2; 1 (n-8)^2 n-8]
        fflush(stdout)
	approx = zeros(3, 401);
	for i=1:401
		vec = log([moment{n-1}(1,i); moment{n-5}(1,i); moment{n-9}(1,i)]);
		approx(:,i) = matrix \ vec;
	end
        approx_a_4(n-9,:) = approx(1,:);
        approx_kappa_4(n-9,:) = approx(2,:);
        approx_rho_4(n-9,:) = approx(3,:);
end

%approx_a_free = approx_a_free(:,1:5:2001);
%approx_kappa_free = approx_kappa_free(:,1:5:2001);
%approx_rho_free = approx_rho_free(:,1:5:2001);
