all:
	g++ -std=c++11 test.cpp -o ./build/test

test: all
	./build/test

check: all
	./build/test > ./test.check.txt

clean:
	rm -rf ./build/*
