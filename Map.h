#pragma once

#include<iostream>
#include<fstream>
#include "GraphAL.h"
#include "Player.h"
#include "Matrix.h"

using namespace std;

//Creating the map
class Map
{
private:
	Target* endingTarget; //where we want to go
	int mapSize;
	GraphAL* myMap;	//graph representation of map
	Player* player; //current position

public:

	//constructor
	Map();

	// Color codes for different terrain types on the map
	static const string COLOR_RESET;
	static const string COLOR_GREY;   // Grey (for Mountain)
	static const string COLOR_GREEN;  // Green (for Forest)
	static const string COLOR_YELLOW; // Yellow (for Plain)
	static const string COLOR_BLUE;   // Blue (for Road)

	// Returns a node from the graph at a given vertex index
	nodeAL* getNode(int vertex);
	//void displayMap();

	// Matrix dimensions and actual matrix data
	int numRows;
	int numCol;
	char** mapMatrix;

	// Prints the matrix representation of the map.
	void printMatrix();

	//Updating Graph
	void updateEdges(int current, int target);
	
	// Testing
	//void updateGraph();
	//bool isValidNode(int target);

	// Player Movement
	bool movePlayer();
	void movePlayer(Player* player);
	

	// Populates the graph based on the matrix data.
	void populateGraph();

	// Adds edges to a node in all four directions around it
	void addEdges(int currentNode, double currentWeight, int i, int j);
	void addDirectedEdge(int currentNode, double currentWeight, int i, int j);
	
	// Initializes the player and target based on characters in the map
	void initializeEntities(char currentChar, int i, int j, int currentNode, int& targets);

	// Creates a player at a specified location
	void createPlayer(int i, int j, int currentNode, int& targets);


};

//tuple<int, int> countRowsAndColumns(const string& filename);
double getSymbolWeight(char symbol);

