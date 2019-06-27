CC=g++

dual: dual.cc dual.h
	$(CC) -std=c++17 -Wall -Wextra -flto -O3 -o dual dual.cc

clean:
	-rm -rf dual
