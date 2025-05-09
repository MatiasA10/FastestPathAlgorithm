#include "Priority_Queue.h"

PriorityQueue::PriorityQueue(int c) //constructor
{
	capacity = c;
	nelements = 0;

	queue = new QueueNode[c];
}

PriorityQueue::~PriorityQueue() //destructor
{
	delete[] queue;
}

int PriorityQueue::getParent(int child)
{
	if (child % 2 == 0)
		return(child / 2) - 1;
	else
		return child / 2;
}

int PriorityQueue::getLeftChild(int parent)
{
	return(2 * parent + 1);
}

int PriorityQueue::getRightChild(int parent)
{
	return(2 * parent + 2);
}

void PriorityQueue::minHeapify(int i, int size)
{
	int left, right, smallest;

	left = 2 * i + 1; //index left of child
	right = 2 * i + 2; //index right of child
	smallest = i; //initiallize smalles index 

	if ((left < size) && queue[left].weight < queue[i].weight) //compare left with current node
	{
		smallest = left;
	}
	if ((right < size) && queue[right].weight < queue[smallest].weight) //compare right with current smallest node
	{
		smallest = right;
	}
	if (smallest != i) //swap when the smallest index is not the current node index
	{
		swap(queue[i], queue[smallest]); 
		minHeapify(smallest, size);
	}
}

void PriorityQueue::buildMinHeap()
{
	for (int i = nelements / 2 - 1; i >= 0; i--)
	{
		minHeapify(i, nelements);
	}
}

void PriorityQueue::push(int index, int weight)
{
	if (nelements < capacity)  //check to make sure capacity has not been reached
	{
		QueueNode x;
		x.vertex = index;
		x.weight = weight;

		int i = nelements; //starts from last element
		while ((i != 0) && (x.weight < queue[i / 2].weight))
		{
			queue[i] = queue[i / 2];
			i /= 2;
		}
		queue[i] = x;
		nelements++;
		//cout << "Added (" << index << "," << weight << ") size =" << nelements << endl;
	}
	else
	{
		cout << "Queue Full!" << endl;
	}
}

QueueNode PriorityQueue::pop()
{
	if (nelements > 0)
	{
		QueueNode tmp = queue[0]; //store min element
		queue[0] = queue[nelements - 1]; 
		minHeapify(0, nelements); //restore min-heap by heapifying from root
		nelements--; //decrease the number of elemetns in priority queue
		return tmp;
	}
	else
	{
		//if priority queue is empty, return a default queue node
		QueueNode tmp;
		tmp.weight = 0;
		tmp.vertex = -1;
		return tmp;
	}
}

void PriorityQueue::display()
{
	cout << "Priority Queue" << endl;
	cout << "Capacity: " << capacity << endl;
	cout << "nelements: " << nelements << endl;
	for (int i = 0; i < nelements; i++)
	{
		cout << i << ": (" << queue[i].vertex << "," << queue[i].weight << ")" << endl;
	}
	cout << endl;
}

void PriorityQueue::DecreaseKey(int index, double value)
{
	int i = 0;
	bool found = false;
	while ((!found) && (i < nelements)) //search for element with specified index in the priority queue
	{
		if (queue[i].vertex == index)
		{
			queue[i].weight = value; //update weight
			found = true;
		}
		i++; //move to next element
	}
	if (found)
	{
		int child = i - 1; //calcualte indx if the modified element
		int parent = getParent(child);
		while ((queue[child].weight < queue[parent].weight) && (child >= 0 && parent >= 0))
		{
			swap(queue[child], queue[parent]);
			child = parent;
			parent = getParent(child);
		}
	}
}