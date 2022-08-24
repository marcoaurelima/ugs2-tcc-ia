CXX = g++ -std=c++11 -Wall


all:
	@$(CXX) main.cpp -o main
	@./main

run: 
	./main