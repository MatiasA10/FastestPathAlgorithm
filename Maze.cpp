#include "Maze.h"
#include "Matrix.h"

Maze::Maze()
{
    map = new Map();
}

void Maze::run()
{
    string userInput;         // user controls
    bool Continue = true;
    while (Continue)        // game loop
    {

        mainMenu();                 // print controls
        map->printMatrix();        // print map

        cout << "Input: ";
        getline(cin, userInput);

        if (userInput == "n")       //to take next step in maze
        { 
            bool endOfMaze = map->movePlayer();
            if (endOfMaze) {
                cout << "Congratulations! You've reached the end of the maze." << endl;
                break; // End the game loop
            }
        }
        else if (userInput == "q")
        {
            Continue = false;        // quit
        }


        cin.clear();                // clear input buffer

        system("CLS");              // clear console
    }
}

void Maze::mainMenu()
{
    cout << "_____________________________________\n" << endl;
    cout << " Next (n) | " << "Quit (q)" << endl;
    cout << "_____________________________________" << endl;

}