#pragma once
#include "Queue.h"

struct QueueNode
{
	int vertex;
	double weight;
};

class PriorityQueue
{
private:
	int capacity;
	int nelements;
	QueueNode* queue; //pointer to array in min-heap priority queue
	void minHeapify(int i, int size); //maintain min-heap
public:
	PriorityQueue(int c); //constructor initializing c
	~PriorityQueue(); //destructor
	void buildMinHeap();
	void push(int index, int weight); //insert new element
	QueueNode pop();
	void DecreaseKey(int index, double value);
	void display();

	int getParent(int child);
	int getLeftChild(int parent);
	int getRightChild(int parent);

	bool isEmpty() { return(nelements == 0); } //checks if priority queue is empty
	bool isFull() { return(nelements == capacity); } //checks is priority queue is full

};

