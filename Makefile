CXX = g++ -std=c++11 -Wall -Wextra
SRC = ./src
INCLUDE = ./include
BIN = ./bin
OBJ = ./obj

OBJS =  $(OBJ)/main.o \
 		$(OBJ)/Chromosome.o \
		$(OBJ)/NeuralNetwork.o \
		$(OBJ)/Neuron.o \
		$(OBJ)/Population.o \
		$(OBJ)/NeuroEvolutiveEngine.o \
		$(OBJ)/GeneticServer.o 

all: $(OBJS)
	@$(CXX) $(OBJS) -o $(BIN)/main
	@$(BIN)/main


$(OBJ)/main.o: main.cpp
	$(CXX) -c main.cpp -I $(INCLUDE) -o $(OBJ)/main.o

$(OBJ)/Chromosome.o: $(SRC)/GA/Chromosome.cpp
	$(CXX) -c $(SRC)/GA/Chromosome.cpp -I $(INCLUDE) -o $(OBJ)/Chromosome.o

$(OBJ)/Population.o: $(SRC)/GA/Population.cpp
	$(CXX) -c $(SRC)/GA/Population.cpp -I $(INCLUDE) -o $(OBJ)/Population.o

$(OBJ)/Neuron.o: $(SRC)/NN/Neuron.cpp
	$(CXX) -c $(SRC)/NN/Neuron.cpp -I $(INCLUDE) -o $(OBJ)/Neuron.o

$(OBJ)/NeuralNetwork.o: $(SRC)/NN/NeuralNetwork.cpp
	$(CXX) -c $(SRC)/NN/NeuralNetwork.cpp -I $(INCLUDE) -o $(OBJ)/NeuralNetwork.o

$(OBJ)/NeuroEvolutiveEngine.o: $(SRC)/NeuroEvolutiveEngine.cpp
	$(CXX) -c $(SRC)/NeuroEvolutiveEngine.cpp -I $(INCLUDE) -o $(OBJ)/NeuroEvolutiveEngine.o

$(OBJ)/GeneticServer.o: $(SRC)/GeneticServer.cpp
	$(CXX) -c $(SRC)/GeneticServer.cpp -I $(INCLUDE) -o $(OBJ)/GeneticServer.o




run: 
	@./bin/main

clean:
	rm -rf ./obj/*.o