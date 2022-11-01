// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
		cout << "Unable to open or find file";
		return board;
	}

	// get first line
	inFile >> line;

	// used for breaking words
	stringstream s(line);

	// row size
	getline(s, word, ',');
	columnSize = stof(word);

	// column size
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
	for (int i = 0; i < rowSize; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < columnSize; j++)
		{
			cout << board[i][j];
		}
		cout << "\n";
	}

	inFile.close();

	return board;
}

void saveBoard(string fileName, vector<vector<char>> board)
{
	// File pointer
	ofstream outFile;

	// creates and opens a new file
	outFile.open(fileName, ios::out);

	if (!outFile) {
		cout << "File not created!";
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

		cout << "File created successfully!";
		outFile.close();
	}

}

int aliveNeighborSquare(int row, int col, vector<vector<char>> board)
{
	// conut of alive neighbors
	int count = 0;

	// pattern
	// 1 2 3
	// 4 X 9
	// 6 7 8

	// 4
	if (col - 1 >= 0 && board[row][col - 1] == 'x') { count++;  }
	// 9
	if (col + 1 < board[0].size() && board[row][col + 1] == 'x') { count++;  }

	if (row - 1 > 0)
	{
		// 2
		if (board[row - 1][col] == 'x') { count++;  }
		// 1
		if (col - 1 >= 0 && board[row - 1][col - 1] == 'x') { count++;  }
		// 3
		if (col + 1 < board[0].size() && board[row - 1][col + 1] == 'x') { count++;  }
	}

	if (row + 1 < board.size())
	{
		// 7
		if (board[row + 1][col] == 'x') { count++;  }
		// 6
		if (col - 1 >= 0 && board[row + 1][col - 1] == 'x') { count++; }
		// 8
		if (col + 1 < board[0].size() && board[row + 1][col + 1] == 'x') { count++;  }
	}

	return count;
}

vector<vector<char>> gol(vector<vector<char>> board, int generations)
{
	vector<vector<char>> newBoard = board;

	for( int i = 0; i < generations; i++)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[0].size(); j++)
			{
				int aliveNeighbors = aliveNeighborSquare(i, j, board);

				if (aliveNeighbors == 2 || aliveNeighbors == 3) newBoard[i][j] = 'x';
				else newBoard[i][j] = '.';
				cout << newBoard[i][j];
			}
			cout << "\n";
		}
		cout << "\n";
		board = newBoard;
	}
	return newBoard;
}

int main(int argc, char** argv)
{
	string loadFileName;
	string saveFileName;
	int generations = 1;
	bool measure = false;
	int counter;
	vector<vector<char>> board;

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
		cout << "no filename given to load";

	if (saveFileName.empty())
		cout << "no filename given to save";

	if (!loadFileName.empty())
		board = loadBoard(loadFileName);
		board = gol(board, generations);
		saveBoard(saveFileName, board);
	

	return EXIT_SUCCESS;
}
