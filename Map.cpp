#include "Map.h"
#include<tuple>
#include<fstream>
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

//colors for the map
const string Map::COLOR_RESET = "\033[0m";
const string Map::COLOR_GREY = "\033[1;30m";
const string Map::COLOR_GREEN = "\033[1;32m";
const string Map::COLOR_YELLOW = "\033[1;33m";
const string Map::COLOR_BLUE = "\033[1;34m";

//terrain weight
const double MOUNTAIN_WEIGHT = 100;        // ^
const double ROAD_WEIGHT = 1;         // -
const double FOREST_WEIGHT = 50;         // |
const double TARGET_WEIGHT = 1;       // X
const double PLAYER_WEIGHT = 1;        // O
const double PRAIRIE_WEIGHT = 30;      // #

Map::Map() //constructor initialized map using matrix class
{
    Matrix myMatrix; //instance og Matrix
    mapMatrix = myMatrix.matrix; //assigne meber of myMatrix to mapMatrix
    numRows = myMatrix.numRows; //number of rows for matrix
    numCol = myMatrix.numCol; //number of colums to matrix
    populateGraph();

}

// Populates the graph based on the matrix data
void Map::populateGraph() {
    //creating new GraphAL with number of nodes for rows and colums
    myMap = new GraphAL(numRows * numCol);
    int targetCount = 0; //initialize counter to track number of target

    //iterate through each cell
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCol; j++) {
            char currentChar = mapMatrix[i][j]; // Get the character representing terrain at current position
            int currentNode = i * numCol + j; // Calculate node index based on position in the matrix

            //get weight with current character
            double weight = getSymbolWeight(currentChar);
            myMap->setNodeWeight(currentNode, weight);
            myMap->setLandType(currentNode, currentChar);

            addEdges(currentNode, weight, i, j); //add edjes to neiboring nodes based on current node

            initializeEntities(currentChar, i, j, currentNode, targetCount); // Initialize players or targets at the node
        }
    }
}

//add edges to neighboring nodes
void Map::addEdges(int currentNode, double currentWeight, int i, int j) {
    addDirectedEdge(currentNode, currentWeight, i - 1, j); //add to above node
    addDirectedEdge(currentNode, currentWeight, i + 1, j); //add to below node
    addDirectedEdge(currentNode, currentWeight, i, j - 1); //add to left node
    addDirectedEdge(currentNode, currentWeight, i, j + 1); //add to right node
}

// Adds a directed edge between two nodes
void Map::addDirectedEdge(int currentNode, double currentWeight, int i, int j) {
    if (i >= 0 && i < numRows && j >= 0 && j < numCol) { //check if within bounds 
        int adjacentNode = i * numCol + j;      // Calculate the adjacent node index
        char adjacentChar = mapMatrix[i][j];    // Get the terrain character for the adjacent node
        double adjWeight = getSymbolWeight(adjacentChar); // Get weight for the adjacent

        myMap->setDirectedEdge(currentNode, adjacentNode, adjWeight, adjacentChar); // Sets directed edge from currentNode to adjacent node
        myMap->setDirectedEdge(adjacentNode, currentNode, currentWeight, myMap->retrieveEdge(currentNode, currentNode)->landType); // Set a directed edge back from adjacent to current node
    }
}

// Initializes the player and target based on characters in the map
void Map::initializeEntities(char currentChar, int i, int j, int currentNode, int& targets) {
    if (currentChar == 'X')
    {
        endingTarget = new Target(i, j, myMap->retrieveEdge(currentNode, currentNode)); // Create a new target at this node
        //endingTarget->printPos();
    }

    if (currentChar == 'O')
    {
        createPlayer(i, j, currentNode, targets); //crete character associated with cuurentNode
    }

}

//creating player
void Map::createPlayer(int i, int j, int currentNode, int& targets) {
    if (targets == 0) { 
        player = new Player(i, j, myMap->retrieveEdge(currentNode, currentNode)); //create new player at position with an associated edge from currentNode
    }
}


//print map with color text
void Map::printMatrix() {
    for (int i = 0; i < numRows; i++) {
        for (int k = 0; k < 2; k++) { // Print each row twice for 2x2
            cout << "/"; // Left border of the map
            for (int j = 0; j < numCol; j++) {
                string colorCode;
                char terrainSymbol = mapMatrix[i][j];   // Get terrain symbol

                switch (terrainSymbol) {
                case '^':
                    colorCode = COLOR_GREY; // Mountain
                    break;
                case '|':
                    colorCode = COLOR_GREEN; // Forest
                    break;
                case '#':
                    colorCode = COLOR_YELLOW; // Prairie
                    break;
                case '-':
                    colorCode = COLOR_BLUE; // Road
                    break;
                default:
                    colorCode = COLOR_RESET; // Default or unrecognized terrain
                }

                cout << colorCode << terrainSymbol << terrainSymbol << COLOR_RESET; 
            }
            cout << "/\n"; // Right border of the map
        }
    }
}

/*
//display map on screen
void Map::displayMap()
{
    cout << "displayMap" << endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCol; j++) {
            int currentNode = i * numCol + j; //calculate current node based on row and column
            char landtype = myMap->getNodeLandtype(currentNode); //get terrrain 

            double weight = myMap->getNodeWeight(currentNode); //get weight
            cout << "Node " << currentNode << " Weight: " << weight << " Landtype: " << landtype << endl; //output
        }
        cout << endl;
    }
}
*/

// Retrieves the node from the graph using given vertex
nodeAL* Map::getNode(int vertex)
{
    return myMap->retrieveEdge(vertex, vertex);
}

/*tuple<int, int> countRowsAndColumns(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open the file." << endl;
        return make_tuple(0, 0);
    }

    vector<string> lines;
    string line;
    int maxColumns = 0;

    while (getline(file, line)) {
        lines.push_back(line);
        maxColumns = max(maxColumns, static_cast<int>(line.length()));
    }

    int numRows = static_cast<int>(lines.size());
    return make_tuple(numRows, maxColumns);
} */

// Calculates the weight associated with a terrain symbol, influencing movement costs
double getSymbolWeight(char symbol)
{
    switch (symbol)
    {
    case '^': return MOUNTAIN_WEIGHT;
    case '#': return PRAIRIE_WEIGHT;
    case'|': return FOREST_WEIGHT;
    case'O': return TARGET_WEIGHT;
    case'X': return PLAYER_WEIGHT;
    case'-': return ROAD_WEIGHT;
    default: return 1.0;

    }
}

// Updates edges in the graph to reflect current and targeted node connections
void Map::updateEdges(int current, int target) {
    // Edges going into current 
    myMap->retrieveEdge(current - numCol, current)->landType = myMap->getNodeLandtype(current);
    myMap->retrieveEdge(current - numCol, current)->weight = myMap->getNodeWeight(current);

    myMap->retrieveEdge(current + numCol, current)->landType = myMap->getNodeLandtype(current);
    myMap->retrieveEdge(current + numCol, current)->weight = myMap->getNodeWeight(current);

    myMap->retrieveEdge(current - 1, current)->landType = myMap->getNodeLandtype(current);
    myMap->retrieveEdge(current - 1, current)->weight = myMap->getNodeWeight(current);

    myMap->retrieveEdge(current + 1, current)->landType = myMap->getNodeLandtype(current);
    myMap->retrieveEdge(current + 1, current)->weight = myMap->getNodeWeight(current);

    // Edges going into target
    myMap->retrieveEdge(target - numCol, target)->landType = myMap->getNodeLandtype(target);
    myMap->retrieveEdge(target - numCol, target)->weight = myMap->getNodeWeight(target);

    myMap->retrieveEdge(target + numCol, target)->landType = myMap->getNodeLandtype(target);
    myMap->retrieveEdge(target + numCol, target)->weight = myMap->getNodeWeight(target);

    myMap->retrieveEdge(target - 1, target)->landType = myMap->getNodeLandtype(target);
    myMap->retrieveEdge(target - 1, target)->weight = myMap->getNodeWeight(target);

    myMap->retrieveEdge(target + 1, target)->landType = myMap->getNodeLandtype(target);
    myMap->retrieveEdge(target + 1, target)->weight = myMap->getNodeWeight(target);

}

// Moves the player on the map, returns true if the player reaches the target
bool Map::movePlayer()
{
    if (endingTarget->beneathTargetNode->landType != 'X')   //if not on target move
    {
        movePlayer(player); 
    }
    
    if (player->xPos == endingTarget->xPos && player->yPos == endingTarget->yPos) { //if on target end maze
        //cout << "End of maze!" << endl;
        return true; // Target reached
    }
    return false; // Target not reached
}


/*
bool Map::isValidNode(int target) {
    if (myMap->retrieveEdge(target, target)->landType == '#') {
        return false;
    }
    else if (myMap->retrieveEdge(target, target)->landType == 'O') {
        return false;
    }
    else if (myMap->retrieveEdge(target, target)->landType == '-') {
        return false;
    }
    else if (myMap->retrieveEdge(target, target)->landType == 'X') {
        return false;
    }
    else {
        return true;
    }
}
*/

// Executes the movement of the player to a specified node
void Map::movePlayer(Player* player)
{
    double* d = nullptr; // To store distances from the source node
    int* pi = nullptr; // To store predecessor in the shortest path

    int targetNodeVertex = player->playerNode->vertex;      // Vertex index of the player's target position
    int playerNodeVertex = endingTarget->targetNode->vertex; // Vertex index of the end target's position

    myMap->shortestPath(targetNodeVertex, d, pi);   // Compute shortest paths from the player's target node

    if (pi[playerNodeVertex] == -1)  // Check if a path exists
    {
        cout << "No path from player to endingTarget" << endl;
    }
    else
    {
        // Initialize dynamic array for the path
        int pathCapacity = 10; // Initial capacity, adjust as needed
        int* path = new int[pathCapacity];
        int pathLength = 0;

        // Trace the path from target back to the players current node
        while (playerNodeVertex != targetNodeVertex)
        {
            if (pathLength == pathCapacity) {
                // Resize the array if the capacity is reached
                int* newPath = new int[pathCapacity * 2];

                for (int i = 0; i < pathCapacity; i++) {
                    newPath[i] = path[i];   //copy existing path to new array
                }

                delete[] path;
                path = newPath;
                pathCapacity *= 2; //update capacity
            }
            path[pathLength++] = playerNodeVertex; // Store the current node in the path
            playerNodeVertex = pi[playerNodeVertex]; // Movce to predeccessor
        }

        // Move player to the next position on the path
        if (pathLength > 0)
        {
            int nextPosition = path[pathLength - 1]; // Get the next position to move to
            
            if (pathLength > 1) {
                pathLength--;
            }

            // Update matrix to reflect movement
            mapMatrix[player->xPos][player->yPos] = player->beneathPlayerNode->landType;    //update matrix at current pos
            player->xPos = nextPosition / numCol;                       //update X position
            player->yPos = nextPosition % numCol;                       //update y position
            mapMatrix[player->xPos][player->yPos] = player->playerNode->landType;   //update matrix at new position

            // Update graph
            int current = targetNodeVertex;
            int target = nextPosition;

            // Player has found the endingTarget
            if (myMap->retrieveEdge(target, target)->landType == 'X') {
                
                // Update current position for when player moves
                // Set current node's land type  and weight to what's beneath the player
                myMap->retrieveEdge(current, current)->landType = player->beneathPlayerNode->landType;
                myMap->retrieveEdge(current, current)->weight = player->beneathPlayerNode->weight;

                // Set beneathPlayerNode land, weight, and vertex type to target node's land type
                player->beneathPlayerNode->landType = endingTarget->beneathTargetNode->landType;
                player->beneathPlayerNode->weight = endingTarget->beneathTargetNode->weight;
                player->beneathPlayerNode->vertex = endingTarget->beneathTargetNode->vertex;

                // Set target node's land  and wight type to player node's land type
                myMap->retrieveEdge(target, target)->landType = player->playerNode->landType;
                myMap->retrieveEdge(target, target)->weight = player->playerNode->weight;
                player->playerNode->vertex = target;

                updateEdges(current, target); // Update graph edges to reflect changes due to player's movement

                delete[] path;  // Free the dynamically allocated path array
                return;
            }

            // Continue updating graph and matrix if target is not reached
            // Set current node's land type  and weight to what's beneath the player
            myMap->retrieveEdge(current, current)->landType = player->beneathPlayerNode->landType; 
            myMap->retrieveEdge(current, current)->weight = player->beneathPlayerNode->weight;

            // Set beneathPlayerNode land, weight, and vertex type to target node's land type
            player->beneathPlayerNode->landType = myMap->retrieveEdge(target, target)->landType;
            player->beneathPlayerNode->weight = myMap->retrieveEdge(target, target)->weight;
            player->beneathPlayerNode->vertex = myMap->retrieveEdge(target, target)->vertex;

            // Set target node's land  and wight type to player node's land type
            myMap->retrieveEdge(target, target)->landType = player->playerNode->landType;
            myMap->retrieveEdge(target, target)->weight = player->playerNode->weight;
            player->playerNode->vertex = target;

            // Update edges related to the movement from current node to target node
            updateEdges(current, target); // Update graph edges to reflect changes due to player's movement
        }

        delete[] path;  // Always ensure to delete the path array to prevent memory leaks
    }
    
    delete[] d;
    delete[] pi;
}

