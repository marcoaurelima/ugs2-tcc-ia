CXX = g++ -std=c++11


all:
	@$(CXX) main.cpp -o main
	@./main

run: 
	./main