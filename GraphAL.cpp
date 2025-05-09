#include "GraphAL.h"
#include "Timer.h"

//constructor
nodeAL::nodeAL() 
{
	vertex = 0;
	weight = 0;
	landType = ' ';
	next = nullptr;
}

// Constructor with vertex and weight parameters
nodeAL::nodeAL(int v, double w)
{
	vertex = v;
	weight = w;
	landType = ' ';
	next = nullptr;
}

// Constructor with vertex, weight, and land type
nodeAL::nodeAL(int v, double w, char type) {
	vertex = v;
	weight = w;
	landType = type;
	next = nullptr;
}

// Default constructor for GraphAL
GraphAL::GraphAL()
{
	n = 0;
	a = nullptr;
	current = nullptr;
	degree = nullptr;
}

// Constructor initializing graph with n vertices
GraphAL::GraphAL(int n1)
{
	n = n1;					// Set the number of vertices
	a = new nodeAL * [n];	// Allocate memory for adjacency list pointers
	degree = new int[n];	// Allocate memory for degree array
	current = new nodeAL * [n];  // Allocate memory for current pointers

	for (int i = 0; i < n; i++)	// For each vertex
	{
		a[i] = new nodeAL(i, 0); // Create a node with default weight 0
		current[i] = nullptr;    // Start with no current node
		degree[i] = 0;           // No edges initially
	}
}

// Destructor to clean up memory
GraphAL::~GraphAL()
{
	for (int i = 0; i < n; i++)
	{
		nodeAL* current = a[i];  // Start with the first node in list
		while (current)			// While there are more nodes
		{
			nodeAL* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] a;
	delete[] current;
	delete[] degree;
}

// Checks existence of an edge between v1 and v2
bool GraphAL::existEdge(int v1, int v2) //check if there is an edge between two vertices
{
	if (v1 < n) // Check if v1 is a valid vertex
	{
		nodeAL* cursor = a[v1]; // Start with the head of the adjacency list for v1

		while (cursor) // While there are more nodes in the list
		{
			if (cursor->vertex == v2) // If the vertex matches v2
			{
				return true;	// Then the edge exist
			}
			else
			{
				cursor = cursor->next;	// Move to next node
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

// Returns the weight of the edge between v1 and v2
double GraphAL::getEdgeWeight(int v1, int v2)
{
	if (v1 < n)
	{
		nodeAL* cursor = a[v1];
		while (cursor != nullptr) // Traverse list
		{
			if (cursor->vertex == v2)
			{
				return cursor->weight;
			}
			else
			{
				cursor = cursor->next;
			}
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

// Sets a directed edge from v1 to v2 with weight w
void GraphAL::setDirectedEdge(int v1, int v2, double w)
{
	if (!existEdge(v1, v2))
	{
		nodeAL* newNode = new nodeAL(v2, w);
		//if list is empty add the new node
		if (a[v1] == nullptr) {
			a[v1] = newNode;
		}
		else {
			//traverse to the end
			nodeAL* current = a[v1];
			while (current->next != nullptr) {
				current = current->next;
			}

			current->next = newNode;
		}
		degree[v1]++;
	}
}

// Sets a directed edge with weight and land type
void GraphAL::setDirectedEdge(int v1, int v2, double w, char type) {
	if (!existEdge(v1, v2))
	{
		nodeAL* newNode = new nodeAL(v2, w, type);
		//if list is empty add the new node
		if (a[v1] == nullptr) {
			a[v1] = newNode;
		}
		else {
			//traverse to the end
			nodeAL* current = a[v1];
			while (current->next != nullptr) {
				current = current->next;
			}

			current->next = newNode;
		}
		degree[v1]++;
	}
}


void GraphAL::removeDirectedEdge(int v1, int v2)
{
	nodeAL* cursor = a[v1];
	nodeAL* previous = nullptr;

	while (cursor != nullptr)
	{
		if (cursor->vertex == v2)
		{
			if (previous == nullptr)
			{
				// This is the first element of the list
				a[v1] = cursor->next;
			}
			else
			{
				// This is not the first element of the list
				previous->next = cursor->next;
			}
			delete cursor;
			degree[v1]--;
			return; // Found and removed the edge, no need to continue.
		}
		previous = cursor;
		cursor = cursor->next;
	}
}

void GraphAL::Display()
{
	for (int i = 0; i < n; i++)
	{
		cout << i << ":";
		nodeAL* cursor = a[i];
		while (cursor)
		{
			cout << cursor->vertex << "(" << cursor->weight << ") " << "Landtype:";
			cout << cursor->landType << " ";
			cursor = cursor->next;
		}
		cout << endl;
	}
}

/*
void GraphAL::setUndirectedEdge(int v1, int v2, double weight, char type) {
	setDirectedEdge(v1, v2, weight, type);
	setDirectedEdge(v2, v1, weight, type);
}
*/

// Sets the weight of a node
void GraphAL::setNodeWeight(int node, double w) {
	if (node < n) {
		a[node]->weight = w;
	}
}

// Retrieves the node representing an edge
nodeAL* GraphAL::retrieveEdge(int v1, int v2) //retrieves edge(node v2 in list of v1)
{
	if (v1 < n)
	{
		nodeAL* cursor = a[v1];
		while (cursor != nullptr)
		{
			if (cursor->vertex == v2)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
	}
	else
	{
		return nullptr;
	}
}

// ITERATOR FUNCTIONS

// Checks if there is an adjacent vertex for vertex u
bool GraphAL::ExistAdjacent(int u)
{
	return current[u] != nullptr;
}

// Sets the current vertex for iteration
void GraphAL::SetCurrentVertex(int u)
{
	current[u] = a[u];
}

// Retrieves the next adjacent vertex
int GraphAL::GetNextAdjacent(int u)
{
	int v = current[u]->vertex;
	current[u] = current[u]->next;
	return v;
}

// Dijkstra Shortest Path
void GraphAL::shortestPath(int s, double*& d, int*& pi) {
	Timer timer; // Create a timer
	timer.startTimer(); // Start the timer before the algorithm starts

	d = new double[n];	//Distance
	pi = new int[n];	//Predecessor

	PriorityQueue* V = new PriorityQueue(n); // Create a priority queue

	Queue* S = new Queue; // Create a queue for storing vertices

	for (int u = 0; u < n; u++) //Initialize distances and predecessors
	{
		d[u] = INT_MAX;  // Set initial distance to "infinity"
		pi[u] = -1;       // No predecessor initially
	}

	d[s] = 0;	//Source Distance = 0

	for (int u = 0; u < n; u++) { // Push (Vertex,Distance) into Priority Queue
		V->push(u, d[u]);
	}

	while (!V->isEmpty())  // While there are vertices to process
	{
		// Pop Vertex From Priority Queue and Iterate
		QueueNode out = V->pop(); // Pop vertex with minimum distance
		S->Enqueue(out.vertex);   // Enqueue it
		int u = out.vertex;		// Current vertex to process
		SetCurrentVertex(u);	// Set current to head of list for u

		while (ExistAdjacent(u)) // Relax
		{
			int v = GetNextAdjacent(u);  // Get adjacent vertex
			double w = getEdgeWeight(u, v); // Get weight of edge
			if (d[v] > d[u] + w)   // Relax edge
			{
				d[v] = d[u] + w;  // Update distance
				pi[v] = u;        // Update predecessor
				V->DecreaseKey(v, d[v]);  // Update priority queue
			}
		}
	}

	delete V;	// Delete priority queue
	delete S;	//Delete queue

	timer.endTimer(); // Stop the timer after the algorithm ends
}

// Displays the shortest path distances and predecessors
void GraphAL::DisplayShortestPath(double* d, int* pi, int n) {
	for (int i = 0; i < n; i++) // For each vertex
	{
		cout << "Vertex: " << i
			<< " : d=" << d[i]
			<< " : pi=" << pi[i]
			<< endl;
	}
	cout << endl;
}

// Retrieves the weight of a node
double GraphAL::getNodeWeight(int node) {
	if (node < n) {
		return a[node]->weight;
	}
	return 0.0;
}

// Sets the land type of a node
void GraphAL::setLandType(int node, char c) {
	if (node < n) {
		a[node]->landType = c;
		//cout << "a[" << node << "]->landType: " << a[node]->landType << endl;
	}
	return;
}

// Retrieves the land type of a node
char GraphAL::getNodeLandtype(int node) {
	if (node < n) {

		return a[node]->landType;
	}
	return 'u';
}

