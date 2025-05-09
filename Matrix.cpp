#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Constructor initializes the matrix and decides which map file to load based on user input
Matrix::Matrix() : matrix(nullptr), numRows(0), numCol(0) { //initialized with 0 rows, 0 col
    std::cout << "Enter the map number to load (1-5): ";
    int choice;
    std::cin >> choice;

    // Switch statement to determine the filename based on user input
    string filename;
    switch (choice) {
    case 1:
        filename = "Map1.txt";
        break;
    case 2:
        filename = "Map2.txt";
        break;
    case 3:
        filename = "Map3.txt";
        break;
    case 4:
        filename = "Map4.txt";
        break;
    case 5:
        filename = "Map5.txt";
        break;
    default:
        cerr << "Invalid input. Defaulting to Map1.txt\n";
        filename = "Map1.txt";
    }

    // Attempt to open the specified file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    readMapFromFile(file);
    file.close();
}

// Reads the map data from a file and stores it in the matrix
void Matrix::readMapFromFile(ifstream& file) {
    string line;
    int rowCapacity = 10;  // Initial capacity for rows
    matrix = new char* [rowCapacity];

    while (getline(file, line)) {     // Read each line from the file
        if (numRows == rowCapacity) { // Check if more space is needed
            // double the capacity if more space is needed
            int newCapacity = rowCapacity * 2;
            char** newMatrix = new char* [newCapacity];

            for (int i = 0; i < rowCapacity; ++i) {
                newMatrix[i] = matrix[i];  // Copy existing rows to new matrix
            }
            delete[] matrix; // Free old matrix
            matrix = newMatrix;  // Assign new matrix
            rowCapacity = newCapacity;  // Update capacity tracker
        }

        int lineLength = line.length();
        matrix[numRows] = new char[lineLength];  // Allocate space for new row

        for (int i = 0; i < lineLength; ++i) {
            matrix[numRows][i] = line[i];      // Copy characters to new row
        }

        if (numRows == 0) {
            numCol = lineLength; // Set the number of columns based on the first line
        }

        else if (lineLength != numCol) {
            cerr << "error inconsistent line length." << endl;
            return;
        }
        numRows++; // Increase the count of rows
    }
}

// Fills the matrix with data from a string array
void Matrix::createMapMatrix(const string* lines, int numRows, int numCol) {
    matrix = new char* [numRows]; //allocate memory for matric rows and columns
    for (int i = 0; i < numRows; i++) {
        matrix[i] = new char[numCol];  // Allocate each row
    }

    for (int i = 0; i < numRows; i++) { //populate matrix with characters
        for (int j = 0; j < numCol; j++) {
            if (j < lines[i].length()) {
                matrix[i][j] = lines[i][j]; //copy characters to matrix
            }
            else {
                matrix[i][j] = '#'; //fill empty edge spaces
            }
        }
    }
}

//destroy map
void Matrix::destroyMapMatrix() {
    if (matrix != nullptr) {
        for (int i = 0; i < numRows; i++) {
            delete[] matrix[i];  // Free each row
        }
        delete[] matrix;   // Free the row pointers
        matrix = nullptr;
    }

}

//for testing 
 /* void Matrix::printMatrix() {
    cout << "Attempting to print matrix..." << endl;
    if (matrix == nullptr || numRows == 0 || numCol == 0) {
        cout << "Matrix is empty or not initialized." << endl;
        return;
    }

    cout << "Matrix Content:" << endl;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCol; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}
*/