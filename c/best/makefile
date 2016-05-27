CC = g++
FILES = main.cpp fib.cpp sequences_linear_one_dim.cpp sequences_linear_two_dim.cpp sequences_ring_one_dim.cpp sequences_ring_two_dim.cpp compute_eigen_value_two_dim.cpp compute_eigen_value_one_dim.cpp
OUT_EXE = main


build: $(FILES)
	        $(CC) -o $(OUT_EXE) $(FILES)

clean:
	        -rm main

rebuild: clean build
