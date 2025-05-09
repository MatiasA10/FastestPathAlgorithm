Matrix.h
	responsible for dynamically managing a 2D array that represents the Maze map. The constructor initializes an empty matrix and loads map data 
	from a specified file ("Map.txt"), handling the matrix's dynamic resizing as needed based on the input file's content. Key functions include 
	readMapFromFile() for reading and constructing the matrix row by row and createMapMatrix() for building the matrix from a array

GraphAL.h
	This file contains the nodeAL and GraphAL classes, which represent and manage the Maze map as a graph. Each nodeAL 
	is a part of the graph and stores information about a point on the map, including its number, weight, type of land it represents, 
	and connections to other points. The GraphAL class uses these nodes to build the entire graph, storing each node's connections in a list format.

Queue.h
	This file has a queue class that is made off of a singly linked list and is used for storing edges for the shortest path algorithm

Priority_Queue.h
	This file holds our Priority Queue, which uses a min-heap structure based on edge weights to manage priorities efficiently. The priority queue 
	is used for the shortest path algorithm, as it helps to quickly access and process the next most promising node or edge based on the lowest weight.

Map.h
	This file has the Map class which creates and manages the Maze's map. It uses a matrix to visually depict various terrains, using distinct 
	colors to enhance the representation: grey for mountains, green for forests, yellow for plains, and blue for roads. The Map class utilizes the GraphAL 
	class to structure the map as a graph, enabling effective pathfinding. Functions include initializing the map with terrain and color data, managing player 
	and target placements, and handling dynamic interactions like player movements and navigation around obstacles. The Dijsktra shortest path algorithms 
	is integrated to make efficient movements towards the target, dynamically updating the map and players position based on each move.

Maze.h
	This file holds the Maze class which has a pointer to the Map. The constructor initializes a new map, and the functions manage running the maze. 
	The mainMenu function displays the controls to the user, with options of advancing through the maze or quitting the maze. The run function is what takes
	the user input for controlling the maze and runs until the user quits or reaches the end of the maze.

Player.h
	This file holds the Player and Target classes. Both classes manage an entity's position within the game using xPos and yPos coordinates and store information 
	about the current node (nodeAL) and the node directly beneath them. Constructors initialize these entities at specified positions and nodes on the game map. The 
	printPos() function in each class provides a display of the entity’s current position and node. These classes tracking player movements and interactions within 
	the game environment.

Timer.h
	This file holds the Timer struct which measures elapsed time in milliseconds. The startTimer() function captures the starting time, and endTimer() calculates and 
	prints the duration since the timer was started. .