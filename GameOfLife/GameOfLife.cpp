#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Timing.h"

using namespace std;

vector<vector<char>> loadBoard(string fileName)
{
	vector<vector<char>> board;
	string line;
	string word;
	int rowSize;
	int columnSize;

	// Open a file in read mode
	ifstream inFile(fileName);

	if (inFile.fail())
	{
		cout << "\n--> Unable to open or find file!";
		return board;
	}

	// get first line
	inFile >> line;

	// used for breaking words
	stringstream s(line);

	// column size
	getline(s, word, ',');
	columnSize = stof(word);

	// row size
	getline(s, word);
	rowSize = stof(word);

	// save each line to vector board 
	for (int r = 0; r < rowSize; r++)
	{
		vector<char> tmp;
		inFile >> line;

		// save each character in line to a vector
		for (char letter : line)
		{
			tmp.push_back(letter);
		}

		board.push_back(tmp);
	}
	cout << "\n";

	// print board
	/*cout << "\nInput:\n";
	for (int i = 0; i < rowSize; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < columnSize; j++)
		{
			cout << board[i][j];
		}
		cout << "\n";
	}
	*/
	inFile.close();

	cout << "--> Board loaded successfully!\n";

	return board;
}

void saveBoard(string fileName, vector<vector<char>> board)
{
	// File pointer
	ofstream outFile;

	// creates and opens a new file
	outFile.open(fileName, ios::out);

	if (!outFile) {
		cout << "\n--> File not created!";
	}
	else {

		// save rows and columns in first line
		outFile << board[0].size() << "," << board.size() << std::endl;

		// save board
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[0].size(); j++)
			{
				outFile << board[i][j];
			}
			outFile << endl;
		}
		outFile.close();

		// print board
		/*cout << " Output:\n";
		for (int i = 0; i < board.size(); i++)
		{
			cout << i << ": ";
			for (int j = 0; j < board[0].size(); j++)
			{
				cout << board[i][j];
			}
			cout << "\n";
		}*/
		cout << "--> Board saved successfully!\n";
	}

}

vector<vector<char>> gol(vector<vector<char>> board, int generations)
{
	vector<vector<char>> nextBoard = board;
	int aliveNeighbors = 0;
	int colSize = board[0].size();

	for( int g = 1; g <= generations; g++)
	{
		//cout << "\n";
		//cout << "Generation " << g << ":\n";

		for (int row = 0; row < board.size(); row++)
		{
			for (int col = 0; col < colSize; col++)
			{

				// count of alive neighbors
				aliveNeighbors = 0;

				// pattern
				// 1 2 3
				// 4 X 9
				// 6 7 8

				// case for cell "X" is not on the border & corners (no wrap around needed)
				if (row > 0 && row < board.size() - 1 && col > 0 && col < colSize - 1)
				{
					// 1 
					if (board[row - 1][col - 1] == 'x') { aliveNeighbors++; }

					// 2
					if (board[row - 1][col] == 'x') { aliveNeighbors++; }

					// 3
					if (board[row - 1][col + 1] == 'x') { aliveNeighbors++; }

					// 4
					if (board[row][col - 1] == 'x') { aliveNeighbors++; }

					// 6
					if (board[row + 1][col - 1] == 'x') { aliveNeighbors++; }

					// 7
					if (board[row + 1][col] == 'x') { aliveNeighbors++; }

					// 8
					if (board[row + 1][col + 1] == 'x') { aliveNeighbors++; }

					// 9
					if (board[row][col + 1] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the top row but not in the top corners
				else if (row == 0 && col > 0 && col < colSize - 1)
				{	
					// 1 wrap around
					if (board[board.size() - 1][col - 1] == 'x') { aliveNeighbors++; }

					// 2 wrap around
					if (board[board.size() - 1][col] == 'x') { aliveNeighbors++; }

					// 3 wrap around
					if (board[board.size() - 1][col + 1] == 'x') { aliveNeighbors++; }

					// 4
					if (board[row][col - 1] == 'x') { aliveNeighbors++; }

					// 6
					if (board[row + 1][col - 1] == 'x') { aliveNeighbors++; }

					// 7
					if (board[row + 1][col] == 'x') { aliveNeighbors++; }

					// 8
					if (board[row + 1][col + 1] == 'x') { aliveNeighbors++; }

					// 9
					if (board[row][col + 1] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the bottom row but not in the bottom corners
				else if (row == board.size() - 1 && col > 0 && col < colSize - 1)
				{
					// 1 
					if (board[row - 1][col - 1] == 'x') { aliveNeighbors++; }

					// 2
					if (board[row - 1][col] == 'x') { aliveNeighbors++; }

					// 3
					if (board[row - 1][col + 1] == 'x') { aliveNeighbors++; }

					// 4
					if (board[row][col - 1] == 'x') { aliveNeighbors++; }

					// 6 wrap around
					if (board[0][col] == 'x') { aliveNeighbors++; }

					// 7 wrap around
					if (board[0][col - 1] == 'x') { aliveNeighbors++; }

					// 8 wrap around
					if (board[0][col + 1] == 'x') { aliveNeighbors++; }

					// 9 
					if (board[row][col + 1] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the left side but not in the corners
				else if (col == 0 && row > 0 && row < board.size() - 1)
				{
					// 1 wrap around
					if (board[row - 1][colSize - 1] == 'x') { aliveNeighbors++; }

					// 2
					if (board[row - 1][col] == 'x') { aliveNeighbors++; }

					// 3
					if (board[row - 1][col + 1] == 'x') { aliveNeighbors++; }

					// 4 wrap around
					if (board[row][colSize - 1] == 'x') { aliveNeighbors++; }

					// 6 wrap around
					if (board[row + 1][colSize - 1] == 'x') { aliveNeighbors++; }

					// 7
					if (board[row + 1][col] == 'x') { aliveNeighbors++; }

					// 8
					if (board[row + 1][col + 1] == 'x') { aliveNeighbors++; }

					// 9
					if (board[row][col + 1] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the right side but not in the corners
				else if (col == colSize - 1 && row > 0 && row < board.size() - 1)
				{
					// 1 
					if (board[row - 1][col - 1] == 'x') { aliveNeighbors++; }

					// 2
					if (board[row - 1][col] == 'x') { aliveNeighbors++; }

					// 3 wrap around
					if (board[row - 1][0] == 'x') { aliveNeighbors++; }

					// 4
					if (board[row][col - 1] == 'x') { aliveNeighbors++; }

					// 6
					if (board[row + 1][col - 1] == 'x') { aliveNeighbors++; }

					// 7
					if (board[row + 1][col] == 'x') { aliveNeighbors++; }

					// 8 wrap around
					if (board[row + 1][0] == 'x') { aliveNeighbors++; }

					// 9 wrap around
					if (board[row][0] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the left top corner
				else if (row == 0 && col == 0)
				{
					// 1 wrap around
					if (board[board.size() - 1][colSize - 1] == 'x') { aliveNeighbors++; }

					// 2 wrap around
					if (board[board.size() - 1][col] == 'x') { aliveNeighbors++; }

					// 3 wrap around
					if (board[board.size() - 1][col + 1] == 'x') { aliveNeighbors++; }

					// 4 wrap around
					if (board[0][colSize - 1] == 'x') { aliveNeighbors++; }

					// 9 
					if (board[0][1] == 'x') { aliveNeighbors++; }

					// 6 wrap around
					if (board[1][colSize - 1] == 'x') { aliveNeighbors++; }

					// 7
					if (board[1][0] == 'x') { aliveNeighbors++; }

					// 8
					if (board[1][1] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the right top corner
				else if (row == 0 && col == colSize - 1)
				{
					// 1 wrap around
					if (board[board.size() - 1][col - 1] == 'x') { aliveNeighbors++; }

					// 2 wrap around
					if (board[board.size() - 1][col] == 'x') { aliveNeighbors++; }

					// 3 wrap around
					if (board[board.size() - 1][0] == 'x') { aliveNeighbors++; }

					// 4 
					if (board[0][col - 1] == 'x') { aliveNeighbors++; }

					// 9 
					if (board[0][0] == 'x') { aliveNeighbors++; }

					// 6 
					if (board[1][col - 1] == 'x') { aliveNeighbors++; }

					// 7
					if (board[1][col] == 'x') { aliveNeighbors++; }

					// 8 wrap around
					if (board[1][0] == 'x') { aliveNeighbors++; }
				}

				// case for cell "X" is on the left bottom corner
				else if (row == board.size() - 1 && col == 0)
				{
					// 1 wrap around
					if (board[row - 1][colSize - 1] == 'x') { aliveNeighbors++; }

					// 2 
					if (board[row - 1][col] == 'x') { aliveNeighbors++; }

					// 3 
					if (board[row - 1][col + 1] == 'x') { aliveNeighbors++; }

					// 4 wrap around
					if (board[row][colSize - 1] == 'x') { aliveNeighbors++; }

					// 9 
					if (board[row][col + 1] == 'x') { aliveNeighbors++; }

					// 6 wrap around
					if (board[0][colSize - 1] == 'x') { aliveNeighbors++; }

					// 7 wrap around
					if (board[0][0] == 'x') { aliveNeighbors++; }

					// 8 wrap around
					if (board[0][1] == 'x') { aliveNeighbors++; }
				}
				
				// case for cell "X" is on the right bottom corner
				else if (row == board.size() - 1 && col == colSize - 1)
				{
					// 1 
					if (board[row - 1][col - 1] == 'x') { aliveNeighbors++; }

					// 2 
					if (board[row - 1][col] == 'x') { aliveNeighbors++; }

					// 3 wrap around
					if (board[row - 1][0] == 'x') { aliveNeighbors++; }

					// 4 
					if (board[row][col - 1] == 'x') { aliveNeighbors++; }

					// 9 wrap around
					if (board[row][0] == 'x') { aliveNeighbors++; }

					// 6 wrap around
					if (board[0][col - 1] == 'x') { aliveNeighbors++; }

					// 7 wrap around
					if (board[0][col] == 'x') { aliveNeighbors++; }

					// 8 wrap around
					if (board[0][0] == 'x') { aliveNeighbors++; }
				}

				// Rule 1
				if (board[row][col] == '.' && aliveNeighbors == 3) { nextBoard[row][col] = 'x';}

				// Rule 2
				if ((board[row][col] == 'x' && aliveNeighbors == 2) || (board[row][col] == 'x' && aliveNeighbors == 3)) { nextBoard[row][col] = 'x'; }

				// Rule 3 & 4
				if ((board[row][col] == 'x' && aliveNeighbors < 2) || (board[row][col] == 'x' && aliveNeighbors > 3)) { nextBoard[row][col] = '.'; }
				
				//cout << nextBoard[i][j];
			}
			//cout << "\n";
		}
		board = nextBoard;
	}
	return board;
}

int main(int argc, char *argv[])
{
	// Get Singleton instance
	Timing* timing = Timing::getInstance();
	// Start recording the setup time
	timing->startSetup();

	string loadFileName;
	string saveFileName;
	int generations = 1;
	bool measure = false;
	int counter;
	vector<vector<char>> board;

	// Handle command line parameters
	if (argc == 1)
		cout << "\nNo Extra Command Line Argument Passed Other Than Program Name";
	if (argc >= 2)
	{
		cout << "\nNumber Of Arguments Passed: " << argc;
		cout << "\n----Following Are The Command Line Arguments Passed----";

		for (counter = 0; counter < argc; counter++)
			printf("\nargv[%d]: %s", counter, argv[counter]);

		for (counter = 0; counter < argc; counter++)
		{
			if (argv[counter] == NULL)
				break;

			if (string(argv[counter]) == "--load" && counter + 1 < argc)
				loadFileName = argv[counter + 1];
				    
			if (string(argv[counter]) == "--save" && counter + 1 < argc)
				saveFileName = argv[counter + 1];

			if (string(argv[counter]) == "--generations" && counter + 1 < argc)
				generations = atoi(argv[counter + 1]);

			if (string(argv[counter]) == "--measure")
				measure = true;
		}
	}

	if (loadFileName.empty())
	{
		cout << "no filename given to load";
		return EXIT_SUCCESS;
	}

	if (saveFileName.empty())
	{
		cout << "no filename given to save";
		return EXIT_SUCCESS;
	}

	// Load board
	board = loadBoard(loadFileName);
	if (board.empty()) return EXIT_SUCCESS;

	// Stop recording the setup time
	timing->stopSetup();

	// Start recording the Calculation time
	timing->startComputation();

	// Calculate new board after n generations
	board = gol(board, generations);

	// Stop recording the Calculation time
	timing->stopComputation();

	// Start recording the Finalization time
	timing->startFinalization();

	cout << "\nGeneration " << generations;

	// Save new board to file
	saveBoard(saveFileName, board);
	
	// Stop recording the Finalization time
	timing->stopFinalization();

	// Save and output this string
	string output = timing->getResults();
	cout << "\nSetup time | Calculation time | Finalization time";
	cout << "\n" << output << "\n";

	return EXIT_SUCCESS;
}
