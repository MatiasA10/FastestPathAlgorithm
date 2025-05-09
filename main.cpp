#include "iostream"
#include "Maze.h"
#include "Map.h"
#include "ctime"
#include "Timer.h"
#include "GraphAL.h"

using namespace std;

void generateRandomGraph(GraphAL& graph, int numVertices, double connectivity, double maxWeight);
void testGraphPerformance(int numVertices, double connectivity, double maxWeight);
void runPartTwo();

int main() {
    int choice;
    char runAgain;

    do {
        cin.clear();                // clear input buffer
        system("CLS");              // clear console

        //chose which project to run
        cout << "ENTER 1 TO CONTINUE WITH PART ONE OR 2 TO RUN PART TWO: ";
        cin >> choice;

        while (choice != 1 && choice != 2) {
            cout << "Invalid input! Please enter either 1 or 2: ";
            cin >> choice;
        }

        if (choice == 1) {
            Maze g;
            g.run(); //part 1 of project
        }
        else if (choice == 2) {
            runPartTwo(); //part 2 of project
        }

        cout << "Do you want to run again? (y/n): "; //asks user if they want to run program again
        cin >> runAgain;
        cin.ignore(); // Clear the newline character from the input buffer

    } while (runAgain == 'Y' || runAgain == 'y');

    return 0;
}


//------------PART TWO---------------------
void runPartTwo() {
    cout << "Running Part Two..." << endl;
    int vertexCounts[] = { 10, 100, 1000 };
    double connectivities[] = { 0.05, 0.25, 0.50, 0.75, 1.00 };
    double maxWeight = 10.0; // Maximum weight for edges

    int vertexCountSize = sizeof(vertexCounts) / sizeof(vertexCounts[0]); // Calculate the number of elements in vertexCounts
    int connectivitySize = sizeof(connectivities) / sizeof(connectivities[0]); // Calculate the number of elements in connectivities

    for (int i = 0; i < vertexCountSize; i++) { //loop over each vertex count
        int vertices = vertexCounts[i];
        for (int j = 0; j < connectivitySize; j++) { //loop over each connectivity value
            double connectivity = connectivities[j];
            cout << "Testing with " << vertices << " vertices and " //display information
                << connectivity * 100 << "% connectivity." << endl;
            testGraphPerformance(vertices, connectivity, maxWeight);
        }
    }
}


void generateRandomGraph(GraphAL& graph, int numVertices, double connectivity, double maxWeight) {
    srand(time(NULL));  // Seed the random number generator

    for (int u = 0; u < numVertices; u++) {
        for (int v = u + 1; v < numVertices; v++) {
            double probability = static_cast<double>(rand()) / RAND_MAX;

            if (probability < connectivity) {
                double weight = 1 + (rand() / (RAND_MAX / (maxWeight - 1)));
                graph.setDirectedEdge(u, v, weight);
                graph.setDirectedEdge(v, u, weight); // Assuming undirected graph, remove if directed
            }
        }
    }
}

void testGraphPerformance(int numVertices, double connectivity, double maxWeight) {
    GraphAL graph(numVertices);
    generateRandomGraph(graph, numVertices, connectivity, maxWeight);

    double* distances = new double[numVertices];  // Array to store distances
    int* predecessors = new int[numVertices];     // Array to store predecessors

    // Assuming graph.shortestPath calculates paths from a specified source
    graph.shortestPath(0, distances, predecessors); // Assuming the source is vertex 0

    // Clean up
    delete[] distances;
    delete[] predecessors;
}