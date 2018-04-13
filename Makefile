all:
	g++ -O0 -g -std=c++11 tests/main.cc -o ./build/test

test: all
	./build/test

debug:
	gdb ./build/test

clean:
	rm -rf ./build/*
