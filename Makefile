all:
	g++ test.cpp -o ./build/test -std=c++14
	./build/test

dbs:
	g++ dbs.cpp -o ./build/dbs -std=c++14
