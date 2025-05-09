#include "Player.h"

Target::Target() //default constructor
{
	xPos = 0;
	yPos = 0;
	targetNode = new nodeAL();
	beneathTargetNode = new nodeAL();

}

Target::Target(int x, int y, nodeAL* pnode) //paramater constructor
{
	xPos = x;
	yPos = y;
	targetNode = new nodeAL(pnode->vertex, pnode->weight, pnode->landType);
	beneathTargetNode = new nodeAL(targetNode->vertex, 1, ' ');
}

void Target::printPos() //print the target
{
	cout << xPos << "," << yPos << endl;
	cout << "Target Node: " << targetNode->landType << " " << targetNode->vertex << " " << targetNode->weight << endl;
	cout << "Beneath Target Node: " << beneathTargetNode->landType << " " << beneathTargetNode->vertex << " " << beneathTargetNode->weight << endl;
}

Player::Player() { //default constructor
	xPos = 0;
	yPos = 0;
	playerNode = new nodeAL();
	beneathPlayerNode = new nodeAL();
}

Player::Player(int x, int y, nodeAL* eNode) { //paramater constructor
	xPos = x;
	yPos = y;
	playerNode = new nodeAL(eNode->vertex, eNode->weight, eNode->landType);
	beneathPlayerNode = new nodeAL(playerNode->vertex, 1, ' ');
}

void Player::printPos() { //print the player
	cout << xPos << "," << yPos << endl;
	cout << "Player Node: " << playerNode->landType << " " << playerNode->vertex << " " << playerNode->weight << endl;
	cout << "Beneath Player Node: " << beneathPlayerNode->landType << " " << beneathPlayerNode->vertex << " " << beneathPlayerNode->weight << endl;
}

