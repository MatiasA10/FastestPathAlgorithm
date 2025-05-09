#pragma once
#include<tuple>
#include<fstream>
#include<iostream>
using namespace std;


class Matrix {
private:

public:
	//contructor
	Matrix();

	void readMapFromFile(ifstream& file);	//read map from file
	void createMapMatrix(const string* lines, int numRows, int numCol); //create map matrix 
	char** matrix;
	int	numRows;
	int numCol;

	void destroyMapMatrix(); //destructor
	//void printMatrix();
};
