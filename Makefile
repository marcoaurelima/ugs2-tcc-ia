CXX = g++ -std=c++11 -Wall
SRC = ./src
INCLUDE = ./include
BIN = ./bin
OBJ = ./obj

OBJS =  $(OBJ)/main.o \
 		$(OBJ)/Chromosome.o \
		$(OBJ)/Connection.o \
		$(OBJ)/NeuralNetwork.o \
		$(OBJ)/Neuron.o \
		$(OBJ)/Population.o 

all: $(OBJS)
	$(CXX) $(OBJS) -o $(BIN)/main
	$(BIN)/main


$(OBJ)/main.o: main.cpp
	$(CXX) -c main.cpp -I $(INCLUDE) -o $(OBJ)/main.o

$(OBJ)/Chromosome.o: $(SRC)/Chromosome.cpp
	$(CXX) -c $(SRC)/Chromosome.cpp -I $(INCLUDE) -o $(OBJ)/Chromosome.o

$(OBJ)/Connection.o: $(SRC)/Connection.cpp
	$(CXX) -c $(SRC)/Connection.cpp -I $(INCLUDE) -o $(OBJ)/Connection.o

$(OBJ)/NeuralNetwork.o: $(SRC)/NeuralNetwork.cpp
	$(CXX) -c $(SRC)/NeuralNetwork.cpp -I $(INCLUDE) -o $(OBJ)/NeuralNetwork.o

$(OBJ)/Neuron.o: $(SRC)/Neuron.cpp
	$(CXX) -c $(SRC)/Neuron.cpp -I $(INCLUDE) -o $(OBJ)/Neuron.o

$(OBJ)/Population.o: $(SRC)/Population.cpp
	$(CXX) -c $(SRC)/Population.cpp -I $(INCLUDE) -o $(OBJ)/Population.o




run: 
	./bin/main

clean:
	rm -rf ./obj/*.o