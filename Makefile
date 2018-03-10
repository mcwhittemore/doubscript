all:
	g++ test.cpp -o ./build/test -std=c++14
	./build/test

doub:
	g++ doub.cpp -o ./build/doub -std=c++14
