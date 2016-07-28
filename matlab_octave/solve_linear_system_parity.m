%% Produce local approximation of sufrace press and energy energy
%% from finite dimensional system.

%load 2_16_-10_10_hundredth_moments.txt
width = 401;
%load checkboard_moments.txt
approx_a = zeros(9, width);
approx_kappa = zeros(9, width);
approx_rho = zeros(9, width);
moment = moments

%moment = checkboard_1

for n=6:14
	matrix = [1 n^2 n; 1 (n-2)^2 n-1; 1 (n-4)^2 n-2]
        fflush(stdout)
	approx = zeros(3, width);
	for i=1:width
		vec = log([moment{n-1}(1,i); moment{n-3}(1,i); moment{n-5}(1,i)]);
		approx(:,i) = matrix \ vec;
	end
        approx_a(n-5,:) = approx(1,:);
        approx_kappa(n-5,:) = approx(2,:);
        approx_rho(n-5,:) = approx(3,:);
end

%approx_a_free = approx_a_free(:,1:5:2001);
%approx_kappa_free = approx_kappa_free(:,1:5:2001);
%approx_rho_free = approx_rho_free(:,1:5:2001);
