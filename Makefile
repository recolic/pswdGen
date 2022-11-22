build:
	g++ main.cpp -O3 -std=c++17 -static -static-libgcc -o pswdGen
	strip pswdGen
