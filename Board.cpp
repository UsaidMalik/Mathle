// its probably best to create the board as a class
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

struct numberInformation {
	string number;
	size_t rowLocation;
	size_t columnLocation;
	bool horizontallyOccupied = false;
	bool verticallyOccupied = false;
};

// now that the board is done i need to fill it with equations. any horizontal or 
// vertical can have equations but the equations must be 5 letters. 

// im basically randomly laying tiles of length 5 by 1 on a grid 
// and the tiles can overlap only if some conditions are met


class Board{

    public:
        // all i really need is the size
        Board(size_t boardSize) {
            board = generateBoard(boardSize);
        }


    private:

        vector<vector<string>> generateBoard(size_t boardSize) {
            vector<vector<string>> board;
            
            //This code here creates the initial rows and columns for the board (it is square)
            vector<string> initialRow;
            for (size_t i = 0; i < boardSize; ++i) {
                initialRow.push_back("#");
            }

            //This code adds all the things to the board.
            for (size_t i = 0; i < boardSize; ++i) {
                board.push_back(initialRow);
            }
            return board;
        }

        vector<vector<string>> board;
};