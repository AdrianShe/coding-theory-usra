%% Produce local approximation of sufrace press and energy energy
%% from finite dimensional system.

%load 2_16_-10_10_hundredth_moments.txt

approx_a = zeros(13, 401);
approx_kappa = zeros(13, 401);
approx_rho = zeros(13, 401);

for n=4:16
	matrix = [1 n^2 n; 1 (n-1)^2 n-1; 1 (n-2)^2 n-2]
        fflush(stdout)
	approx = zeros(3, 401);
	for i=1:401
		vec = log([moment{n-1}(1,i); moment{n-2}(1,i); moment{n-3}(1,i)]);
		approx(:,i) = matrix \ vec;
	end
        approx_a(n-3,:) = approx(1,:);
        approx_kappa(n-3,:) = approx(2,:);
        approx_rho(n-3,:) = approx(3,:);
end
