build:
	g++ -std=c++11 test.cpp -o ./build/test


test: build
	./build/test

check: build
	./build/test > ./test.check.txt
