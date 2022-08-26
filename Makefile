CXX = g++ -std=c++11 -Wall
SRC = Chromosome.cpp Population.cpp

all:
	@$(CXX) main.cpp $(SRC) -o ./bin/main
	@./bin/main

run: 
	./bin/main