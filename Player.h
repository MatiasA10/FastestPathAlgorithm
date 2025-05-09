#pragma once
#include<iostream>
#include "GraphAL.h"
using namespace std;

class Player {
public:
	int xPos;
	int yPos;
	nodeAL* playerNode;
	nodeAL* beneathPlayerNode;

	Player(); //default constructor
	Player(int x, int y, nodeAL* eNode); //parameter cosntructor

	void printPos();
};

class Target {
public:
	Target(); //default constructor
	Target(int x, int y, nodeAL* pnode); //parameter cosntructor

	void printPos();

	int xPos;
	int yPos;
	nodeAL* targetNode;
	nodeAL* beneathTargetNode;

};

