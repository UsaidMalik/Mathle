#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;


/*

Author Usaid malik

this works two fold. I first need to generate and fill a random board with equations that are each 5 by 5. 

I then use the pivots of those equations which are the operators to generate new equations. 

This has to be done randomly but i may be able to train a model to do it for me

Once im done doing that i have to randomly remove pieces from the bord and then give it to teh user to solve

if both are solved then the board works

// the main issue currently is generating the board itself. 
*/
struct numberInformation {
	string number;
	size_t rowLocation;
	size_t columnLocation;
	bool horizontallyOccupied = false;
	bool verticallyOccupied = false;
};


vector<vector<string>> generateBoard(size_t boardSize);
numberInformation generateStartingPosition(vector<vector<string>>& board, size_t boardSize);
void generateEquation(vector<vector<string>>& board, const numberInformation& number, vector<string>& numbers);
void placeNonNumbers(vector<vector<string>>& board, numberInformation& firstNumber, numberInformation& secondNumber, numberInformation& hashedNumber);
void displayBoard(const vector<vector<string>>& board);

int main() {
	srand(time(0));
	size_t boardSize;
	cout << "Input a board size (minimum 5): ";
	cin >> boardSize;
	cout << endl;
	while (boardSize < 5)
	{
		cout << "Invalid board size please try again: ";
		cin >> boardSize;
	}
	vector<vector<string>> board = generateBoard(boardSize); // this equation here generates the board
	displayBoard(board); // this is a helper function to display the board 
	

}

// cleared
void horizontalChecks(vector<vector<string>>& board, const numberInformation& number, vector<vector<numberInformation>>& placeNumberAt) {

	if (!number.horizontallyOccupied) {

		size_t row = number.rowLocation;
		size_t column = number.columnLocation;

		numberInformation twoLeft{ "#", row, column - 2 };
		numberInformation twoRight{ "#", row, column + 2 };
		numberInformation fourRight{ "#", row, column + 4 };
		numberInformation fourLeft{ "#", row, column - 4 };

		if (column > 1 && column < board.size() - 2) {

			if (board[row][column + 1] == "#" && board[row][column - 1] == "#") {
				try {
					if (board[row][column + 2] == "#" && board[row][column - 2] == "#") {
						// # # NUM # #
						placeNumberAt.push_back(vector<numberInformation>{twoLeft, twoRight});
					}
					else if ((stoi(board[row][column + 2]) >= 0 || stoi(board[row][column + 2]) < 0)
						&& board[row][column - 2] == "#") {
						// # # NUM # num
						numberInformation numberNew = twoRight;
						numberNew.number = board[row][column + 2];
						placeNumberAt.push_back(vector<numberInformation>{twoLeft, numberNew});
					}
					else if ((stoi(board[row][column - 2]) >= 0 || stoi(board[row][column - 2]) < 0)
						&& board[row][column + 2] == "#") {
						// num # NUM # #
						numberInformation numberNew = twoLeft;
						numberNew.number = board[row][column - 2];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, twoRight});
					}
				} catch(...) {
					cout << "Exception was thrown" << endl;
				}

			}
		}

		if (column < board.size() - 4) {
			// b # # # # # # # # # b 
			if (board[row][column + 1] == "#" && board[row][column + 3] == "#") {
				try {
					if (board[row][column + 2] == "#" && board[row][column + 4] == "#") {
						// NUM # # # #
						placeNumberAt.push_back(vector<numberInformation>{twoRight, fourRight});

					}
					else if ((stoi(board[row][column + 2]) >= 0 || stoi(board[row][column + 2]) < 0)
						&& board[row][column + 4] == "#") {
						// NUM # num # #
						numberInformation numberNew = twoRight;
						numberNew.number = board[row][column + 2];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, fourRight});

					}
					else if (board[row][column + 2] == "#" &&
						(stoi(board[row][column + 4]) >= 0 || stoi(board[row][column + 4]) < 0)) {
						// NUM # # # num
						numberInformation numberNew = fourRight;
						numberNew.number = board[row][column + 4];
						placeNumberAt.push_back(vector<numberInformation>{twoRight, numberNew});
					}
				}
				catch (...) {
					cout << "Exception was thrown" << endl;
				}
			}

		}


		if (column > 3) {
			// b # # # # # b 	8			
			if (board[row][column - 1] == "#" && board[row][column - 3] == "#") {

				try
				{
					if (board[row][column - 2] == "#" && board[row][column - 4] == "#") {
						//# # # # NUM
						placeNumberAt.push_back(vector<numberInformation>{twoLeft, fourLeft});

					}
					else if ((stoi(board[row][column - 2]) >= 0 || stoi(board[row][column - 2]) < 0)
						&& board[row][column - 4] == "#") {
						// # # num # NUM
						numberInformation numberNew = twoLeft;
						numberNew.number = board[row][column - 2];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, fourLeft});
					}
					else if (board[row][column - 2] == "#" &&
						(stoi(board[row][column - 4]) >= 0 || stoi(board[row][column - 4]) < 0)) {
						// num # # # NUM
						numberInformation numberNew = fourLeft;
						numberNew.number = board[row][column - 4];
						placeNumberAt.push_back(vector <numberInformation>{twoLeft, fourLeft});
					}
			} catch (...) {
			cout << "Exception was thrown" << endl;
			}

			}
		}
	}

}

//cleared
void verticalChecks(vector<vector<string>>& board, const numberInformation& number, vector<vector<numberInformation>>& placeNumberAt) {
	if (!number.verticallyOccupied) {

		size_t row = number.rowLocation;
		size_t column = number.columnLocation;

		numberInformation twoLeft{ "#", row - 2, column };
		numberInformation twoRight{ "#", row + 2, column };
		numberInformation fourRight{ "#", row + 4, column };
		numberInformation fourLeft{ "#", row - 4, column };

		if (row > 1 && row < board.size() - 2) {

			if (board[row + 1][column] == "#" && board[row - 1][column] == "#") {
				try {
					if (board[row + 2][column] == "#" && board[row - 2][column] == "#") {
						// # # NUM # #
						placeNumberAt.push_back(vector<numberInformation>{twoRight, twoLeft});
					}
					else if ((stoi(board[row + 2][column]) >= 0 || stoi(board[row + 2][column]) < 0)
						&& board[row - 2][column] == "#") {
						// # # NUM # num		
						numberInformation numberNew = twoRight;
						numberNew.number = board[row + 2][column];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, twoLeft});

					}
					else if ((stoi(board[row - 2][column]) >= 0 || stoi(board[row - 2][column]) < 0)
						&& board[row + 2][column] == "#") {
						// num # NUM # #
						numberInformation numberNew = twoLeft;
						numberNew.number = board[row - 2][column];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, twoRight});
					}
				}
				catch (...) {
					cout << "Exception was thrown" << endl;
				}
			}
		}

		//Over here issues start with edge cases
		if (row < board.size() - 4) {

			if (board[row + 1][column] == "#" && board[row + 3][column] == "#") {
				try {
					if (board[row + 2][column] == "#" && board[row + 4][column] == "#") {
						// NUM # # # #
						placeNumberAt.push_back(vector<numberInformation>{fourRight, twoRight});
					}
					else if ((stoi(board[row + 2][column]) >= 0 || stoi(board[row + 2][column]) < 0)
						&& board[row + 4][column] == "#") {
						// NUM # num # #
						numberInformation numberNew = twoRight;
						numberNew.number = board[row + 2][column];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, fourRight});
					}
					else if (board[row + 2][column] == "#" &&
						(stoi(board[row + 4][column]) >= 0 || stoi(board[row + 4][column]) < 0)) {
						// NUM # # # num
						numberInformation numberNew = fourRight;
						numberNew.number = board[row + 4][column];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, twoRight});
					}
				}
				catch (...) {
					cout << "Exception was thrown" << endl;
				}
			}
		}

		if (row > 3) {

			if (board[row - 1][column] == "#" && board[row - 3][column] == "#") {
				try {
					if (board[row - 2][column] == "#" && board[row - 4][column] == "#") {
						//# # # # NUM
						placeNumberAt.push_back(vector<numberInformation>{twoLeft, fourLeft});
					}
					else if ((stoi(board[row - 2][column]) >= 0 || stoi(board[row - 2][column]) < 0)
						&& board[row - 4][column] == "#") {
						// # # num # NUM
						numberInformation numberNew = twoLeft;
						numberNew.number = board[row - 2][column];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, fourLeft});
					}
					else if (board[row - 2][column] == "#" &&
						(stoi(board[row - 4][column]) >= 0 || stoi(board[row - 4][column]) < 0)) {
						// num # # # NUM
						numberInformation numberNew = fourLeft;
						numberNew.number = board[row - 4][column];
						placeNumberAt.push_back(vector<numberInformation>{numberNew, twoLeft});
					}
				}
				catch (...) {
					cout << "Exception was thrown" << endl;
				}
			}
		}

	}
}

void solveRightEdge(numberInformation& rightEdge, numberInformation& middle, numberInformation& leftEdge,
	vector<vector<string>>& board) {
	int whichOperation = rand() % 4;
	board[rightEdge.rowLocation][rightEdge.columnLocation - 1] = "=";
	middle.horizontallyOccupied = true;
	rightEdge.horizontallyOccupied = true;
	leftEdge.horizontallyOccupied = true;
	if (rightEdge.number == "#") {
		// num + num = #
		if (whichOperation == 0) {
			rightEdge.number = to_string(stoi(middle.number) + stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "+";
		}
		else if (whichOperation == 1) {
			rightEdge.number = to_string(stoi(middle.number) - stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "-";
		}
		else if (whichOperation == 2) {
			rightEdge.number = to_string(stoi(middle.number) * stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "*";
		}
		else if (whichOperation == 3) {
			rightEdge.number = to_string(stoi(middle.number) / stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "/";
		}
		board[rightEdge.rowLocation][rightEdge.columnLocation] = rightEdge.number;
	}
	else if (middle.number == "#") {
		// num + # = num
		if (whichOperation == 0) {
			// num + x = rightEdge
			middle.number = to_string(stoi(rightEdge.number) - stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "+";
		}
		else if (whichOperation == 1) {
			// num - x = redge
			middle.number = to_string(stoi(leftEdge.number) - stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "-";
		}
		else if (whichOperation == 2) {
			// num * x = redge
			middle.number = to_string(stoi(rightEdge.number) / stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "*";
		}
		else if (whichOperation == 3) {
			// num / x = redge
			middle.number = to_string(stoi(leftEdge.number) / stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "/";
		}
		board[middle.rowLocation][middle.columnLocation] = middle.number;
	}
	else if (leftEdge.number == "#") {
		if (whichOperation == 0) {
			// # + mid = r
			leftEdge.number = to_string(stoi(rightEdge.number) - stoi(middle.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "+";
		}
		else if (whichOperation == 1) {
			// # - mid = r
			leftEdge.number = to_string(stoi(rightEdge.number) + stoi(middle.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "-";
		}
		else if (whichOperation == 2) {
			// # * mid = r
			leftEdge.number = to_string(stoi(rightEdge.number) / stoi(middle.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "*";
		}
		else if (whichOperation == 3) {
			// # / mid = r
			leftEdge.number = to_string(stoi(middle.number) * stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation - 1] = "/";
		}
		board[leftEdge.rowLocation][leftEdge.columnLocation] = leftEdge.number;
	}
	
}

void solveLeftEdge(numberInformation& rightEdge, numberInformation& middle, numberInformation& leftEdge, vector<vector<string>>& board) {
	int whichOperation = rand() % 4;
	board[leftEdge.rowLocation][leftEdge.columnLocation + 1] = "=";
	middle.horizontallyOccupied = true;
	rightEdge.horizontallyOccupied = true;
	leftEdge.horizontallyOccupied = true;
	if (leftEdge.number == "#") {
		// # = mid + right;
		if (whichOperation == 0) {
			leftEdge.number = to_string(stoi(middle.number) + stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "+";
		}
		else if (whichOperation == 1) {
			leftEdge.number = to_string(stoi(middle.number) - stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "-";
		}
		else if (whichOperation == 2) {
			leftEdge.number = to_string(stoi(middle.number) * stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "*";
		}
		else if (whichOperation == 3) {
			leftEdge.number = to_string(stoi(middle.number) / stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "/";
		}
		board[leftEdge.rowLocation][leftEdge.columnLocation] = leftEdge.number;
	}
	else if (middle.number == "#") {
		if (whichOperation == 0) {
			// num = x + leftedge
			middle.number = to_string(stoi(leftEdge.number) - stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "+";
		}
		else if (whichOperation == 1) {
			// num = x - leftedge
			middle.number = to_string(stoi(leftEdge.number) + stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "-";
		}
		else if (whichOperation == 2) {
			// ledge = x * redge
			middle.number = to_string(stoi(leftEdge.number) / stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "*";
		}
		else if (whichOperation == 3) {
			// ledge = x / redge
			middle.number = to_string(stoi(leftEdge.number) * stoi(rightEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "/";
		}
		board[middle.rowLocation][middle.columnLocation] = middle.number;
	}
	else if (rightEdge.number == "#") {
		if (whichOperation == 0) {
			// num = middle + #
			rightEdge.number = to_string(stoi(leftEdge.number) - stoi(middle.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "+";
		}
		else if (whichOperation == 1) {
			// num = middle - #
			rightEdge.number = to_string(stoi(middle.number) - stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "-";
		}
		else if (whichOperation == 2) {
			// num = middle * #
			rightEdge.number = to_string(stoi(leftEdge.number) / stoi(middle.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "*";
		}
		else if (whichOperation == 3) {
			// num = middle / x
			rightEdge.number = to_string(stoi(middle.number) / stoi(leftEdge.number));
			board[middle.rowLocation][middle.columnLocation + 1] = "/";
		}
		board[rightEdge.rowLocation][rightEdge.columnLocation] = rightEdge.number;
	}
}

void solveUpperEdge(numberInformation& upperEdge, numberInformation& middle, numberInformation& lowerEdge, vector<vector<string>>& board) {
	int whichOperation = rand() % 4;
	board[upperEdge.rowLocation + 1][upperEdge.columnLocation] = "=";
	middle.verticallyOccupied = true;
	upperEdge.verticallyOccupied = true;
	lowerEdge.verticallyOccupied = true;
	if (upperEdge.number == "#") {
		// num + num = #
		if (whichOperation == 0) {
			upperEdge.number = to_string(stoi(middle.number) + stoi(lowerEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "+";
		}
		else if (whichOperation == 1) {
			upperEdge.number = to_string(stoi(middle.number) - stoi(lowerEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "-";
		}
		else if (whichOperation == 2) {
			upperEdge.number = to_string(stoi(middle.number) * stoi(lowerEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "*";
		}
		else if (whichOperation == 3) {
			upperEdge.number = to_string(stoi(middle.number) / stoi(lowerEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "/";
		}
		board[upperEdge.rowLocation][upperEdge.columnLocation] = upperEdge.number;
	}
	else if (middle.number == "#") {
		// num + # = num
		if (whichOperation == 0) {
			// num + x = rightEdge
			middle.number = to_string(stoi(upperEdge.number) - stoi(lowerEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "+";
		}
		else if (whichOperation == 1) {
			// num - x = redge
			middle.number = to_string(stoi(lowerEdge.number) - stoi(upperEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "-";
		}
		else if (whichOperation == 2) {
			// num * x = redge
			middle.number = to_string(stoi(upperEdge.number) / stoi(lowerEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "*";
		}
		else if (whichOperation == 3) {
			// num / x = redge
			middle.number = to_string(stoi(lowerEdge.number) / stoi(upperEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "/";
		}
		board[middle.rowLocation][middle.columnLocation] = middle.number;
	}
	else if (lowerEdge.number == "#") {
		if (whichOperation == 0) {
			// # + mid = r
			lowerEdge.number = to_string(stoi(upperEdge.number) - stoi(middle.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "+";
		}
		else if (whichOperation == 1) {
			// # - mid = r
			lowerEdge.number = to_string(stoi(upperEdge.number) + stoi(middle.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "-";
		}
		else if (whichOperation == 2) {
			// # * mid = r
			lowerEdge.number = to_string(stoi(upperEdge.number) / stoi(middle.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "*";
		}
		else if (whichOperation == 3) {
			// # / mid = r
			lowerEdge.number = to_string(stoi(middle.number) * stoi(upperEdge.number));
			board[middle.rowLocation + 1][middle.columnLocation] = "/";
		}
		board[lowerEdge.rowLocation][lowerEdge.columnLocation] = lowerEdge.number;
	}

}


void solveLowerEdge(numberInformation& upperEdge, numberInformation& middle,
	numberInformation& lowerEdge, vector<vector<string>>& board) {
	//This variable below checks which operation is going to be used.
	int whichOperation = rand() % 4;
	//This here places an equal above the lower edge
	board[lowerEdge.rowLocation - 1][lowerEdge.columnLocation] = "=";
	middle.verticallyOccupied = true;
	upperEdge.verticallyOccupied = true;
	lowerEdge.verticallyOccupied = true;
	if (lowerEdge.number == "#") {
		//This checks if the lower edge is hashed
		// # = mid + right;
		if (whichOperation == 0) {
			lowerEdge.number = to_string(stoi(middle.number) + stoi(upperEdge.number));
			//This places the operation above the middle edge.
			board[middle.rowLocation - 1][middle.columnLocation] = "+";
		}
		else if (whichOperation == 1) {
			lowerEdge.number = to_string(stoi(middle.number) - stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "-";
		}
		else if (whichOperation == 2) {
			lowerEdge.number = to_string(stoi(middle.number) * stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "*";
		}
		else if (whichOperation == 3) {
			lowerEdge.number = to_string(stoi(middle.number) / stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "/";
		}
		board[lowerEdge.rowLocation][lowerEdge.columnLocation] = lowerEdge.number;
	}
	else if (middle.number == "#") {
		if (whichOperation == 0) {
			// num = x + leftedge
			middle.number = to_string(stoi(lowerEdge.number) - stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "+";
		}
		else if (whichOperation == 1) {
			// num = x - leftedge
			middle.number = to_string(stoi(lowerEdge.number) + stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "-";
		}
		else if (whichOperation == 2) {
			// ledge = x * redge
			middle.number = to_string(stoi(lowerEdge.number) / stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "*";
		}
		else if (whichOperation == 3) {
			// ledge = x / redge
			middle.number = to_string(stoi(lowerEdge.number) * stoi(upperEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "/";
		}
		board[middle.rowLocation][middle.columnLocation] = middle.number;
	}
	else if (upperEdge.number == "#") {
		if (whichOperation == 0) {
			// num = middle + #
			upperEdge.number = to_string(stoi(lowerEdge.number) - stoi(middle.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "+";
		}
		else if (whichOperation == 1) {
			// num = middle - #
			upperEdge.number = to_string(stoi(middle.number) - stoi(lowerEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "-";
		}
		else if (whichOperation == 2) {
			// num = middle * #
			upperEdge.number = to_string(stoi(lowerEdge.number) / stoi(middle.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "*";
		}
		else if (whichOperation == 3) {
			// num = middle / x
			upperEdge.number = to_string(stoi(middle.number) / stoi(lowerEdge.number));
			board[middle.rowLocation - 1][middle.columnLocation] = "/";
		}
		board[upperEdge.rowLocation][upperEdge.columnLocation] = upperEdge.number;
	}

}


void placeNonNumbers(vector<vector<string>>& board, numberInformation& firstNumber, numberInformation& secondNumber, 
	numberInformation& hashedNumber) {
	bool leftOrRightEdge = rand() % 2;
	numberInformation leftEdge;
	numberInformation rightEdge;
	numberInformation upperEdge;
	numberInformation lowerEdge;
	numberInformation middle;
	//Doing this operation since it finds out if it is a horizontal or it is a vertical
	//This column - column means they are ni the same column so were looking at a vertical play
	if ((firstNumber.columnLocation - secondNumber.columnLocation - hashedNumber.columnLocation) == 0) {
		//This one determines how far away the two numbers are. 
		//This goes out to find out what is the position of the numbers
		// and who is middle hashed and right
		// This if statement below means that -> vertically rotated rightwards
		// 1 # 2 # #
		if (hashedNumber.rowLocation - firstNumber.rowLocation == 4) {
			upperEdge = firstNumber;
			lowerEdge = hashedNumber;
			middle = secondNumber;
		}
		//This if block measn this # # 2 # 1
		else if (hashedNumber.rowLocation - firstNumber.rowLocation == -4) {
			upperEdge = hashedNumber;
			lowerEdge = firstNumber;
			middle = secondNumber;
		}
		//This block means this 2 # 1 # #
		else if (hashedNumber.rowLocation - secondNumber.rowLocation == 4) {
			upperEdge = secondNumber;
			lowerEdge = hashedNumber;
			middle = firstNumber;
		}
		// This block means this # # 1 # 2
		else if (hashedNumber.rowLocation - secondNumber.rowLocation == -4) {
			upperEdge = hashedNumber;
			lowerEdge = secondNumber;
			middle = firstNumber;
		}
		//This block means this 2 # # # 1
		else if (firstNumber.rowLocation - secondNumber.rowLocation == 4) {
			upperEdge = secondNumber;
			lowerEdge = firstNumber;
			middle = hashedNumber;
		}
		//This block means this 1 # # # 2 
		else if (firstNumber.rowLocation - secondNumber.rowLocation == -4) {
			upperEdge = firstNumber;
			lowerEdge = secondNumber;
			middle = hashedNumber;
		}
		if (leftOrRightEdge) {
			solveLowerEdge(upperEdge, middle, lowerEdge, board);
		}
		else {
			solveUpperEdge(upperEdge, middle, lowerEdge, board);
		}
	}
	//Here downwards needs a fixing.
	//This one is horizontal ones that do there thing yeah.
	//AKA therse are int eh same row.
	else if ((firstNumber.rowLocation - secondNumber.rowLocation - hashedNumber.rowLocation) == 0) {
		//This means 1 # 2 # #
		if (hashedNumber.columnLocation - firstNumber.columnLocation == 4) {
			rightEdge = hashedNumber;
			leftEdge = firstNumber;
			middle = secondNumber;
		}
		//This means # # 2 # 1 
		else if (hashedNumber.columnLocation - firstNumber.columnLocation == -4) {
			rightEdge = firstNumber;
			leftEdge = hashedNumber;
			middle = secondNumber;
		}
		//This means 2 # 1 # #
		else if (hashedNumber.columnLocation - secondNumber.columnLocation == 4) {
			rightEdge = hashedNumber;
			leftEdge = secondNumber;
			middle = firstNumber;
		}
		//This means # # 1 # 2 
		else if (hashedNumber.columnLocation - secondNumber.columnLocation == -4) {
			rightEdge = secondNumber;
			leftEdge = hashedNumber;
			middle = firstNumber;
		}
		//This means 2 # # # 1
		else if (firstNumber.columnLocation - secondNumber.columnLocation == 4) {
			rightEdge = firstNumber;
			leftEdge = secondNumber;
			middle = hashedNumber;
		}
		//This measn 1 # # # 2
		else if (firstNumber.columnLocation - secondNumber.columnLocation == -4) {
			rightEdge = secondNumber;
			leftEdge = firstNumber;
			middle = hashedNumber;
		}

		//This down needs to be fixed
		if (leftOrRightEdge) {
			solveLeftEdge(rightEdge, middle, leftEdge, board);
		}
		else {
			solveRightEdge(rightEdge, middle, leftEdge, board);
		}

	}
}

void updateVector(vector<numberInformation>& vectorOfNumbers) {
	//remeove any numbers thaht are horizontally adn vertically occupied.
	for (size_t i = 0; i < vectorOfNumbers.size(); ++i) {
		if (vectorOfNumbers[i].horizontallyOccupied && vectorOfNumbers[i].verticallyOccupied) {
			vectorOfNumbers.erase(vectorOfNumbers.begin() + i);
		}
	}
};


void generateEquation(vector<vector<string>>& board, const numberInformation& number, vector<numberInformation>& numbers) {
	vector<vector<numberInformation>> placeNumberAt;
	verticalChecks(board, number, placeNumberAt);
	horizontalChecks(board, number, placeNumberAt);

	bool becomingResultOrSecondNumber = rand() % 2;
	numberInformation firstNumber = number;

	size_t vectorSize = placeNumberAt.size();
	int x = (rand() % vectorSize);
	numberInformation secondNumber = placeNumberAt[x][0];
	numberInformation thirdNumber = placeNumberAt[x][1];

	numbers.push_back(thirdNumber);
	numbers.push_back(secondNumber);

	if (thirdNumber.number == "#" && secondNumber.number == "#") {
		int whichSide = rand() % 2;
		if (whichSide) {
			thirdNumber.number = to_string(rand());
			board[thirdNumber.rowLocation][thirdNumber.columnLocation] = thirdNumber.number;
			placeNonNumbers(board, firstNumber, thirdNumber, secondNumber);
		}
		else {
			secondNumber.number = to_string(rand());
			board[secondNumber.rowLocation][secondNumber.columnLocation] = secondNumber.number;
			placeNonNumbers(board, firstNumber, secondNumber, thirdNumber);
		}
	}
	else if (thirdNumber.number == "#") {
		board[secondNumber.rowLocation][secondNumber.columnLocation] = secondNumber.number;
		placeNonNumbers(board, firstNumber, secondNumber, thirdNumber);
	}
	else if (secondNumber.number == "#") {
		board[thirdNumber.rowLocation][thirdNumber.columnLocation] = thirdNumber.number;
		placeNonNumbers(board, firstNumber, thirdNumber, secondNumber);
	}
	cout << "reached the end of placing numbers in" << endl;

};

vector<vector<string>> generateBoard(size_t boardSize) {
	vector<vector<string>> board;
	numberInformation first_number = generateStartingPosition(board, boardSize);
	vector<numberInformation> numbers;
	numbers.push_back(first_number);
	cout << "here under issues start" << endl;
	while (numbers.size() != 0)
	{
		displayBoard(board);
		generateEquation(board, numbers[0], numbers);
		updateVector(numbers);
	} 
	return board;
}


//No issues here.
numberInformation generateStartingPosition(vector<vector<string>>& board, size_t boardSize) {

	//This code here creates the initial rows for the board
	vector<string> initialRow;
	for (size_t i = 0; i < boardSize; ++i) {
		initialRow.push_back("#");
	}

	//This code adds all the things to the board.
	for (size_t i = 0; i < boardSize; ++i) {
		board.push_back(initialRow);
	}

	//This code sets the initial conditions of the board.
	int startingNumber = rand() % 10;
	int row = rand() % boardSize;
	int column = rand() % boardSize;
	board[row][column] = to_string(startingNumber);
	numberInformation number{ to_string(startingNumber), row, column };
	return number;
}

//No issues here.
void displayBoard(const vector<vector<string>>& board) {
	for (size_t i = 0; i < board.size(); ++i) {
		for (size_t j = 0; j < board[0].size(); ++j) {
			cout << " " << board[i][j];
		}
		cout << endl;
	}
}
