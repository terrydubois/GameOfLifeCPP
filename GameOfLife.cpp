#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// create grid with same width and height
vector<vector<int>> createGrid(int size) {
	vector<vector<int>> grid(size, vector<int>(size, 0));
	return grid;
}

// create grid with glider pattern
vector<vector<int>> createGliderGrid() {

	// create a 25x25 cell grid
	int size = 25;
	vector<vector<int>> grid = createGrid(size);

	// set values in the center, according to glider pattern
	int center = size / 2;
	grid[center - 1][center] = 1;
	grid[center][center + 1] = 1;
	grid[center + 1][center - 1] = 1;
	grid[center + 1][center] = 1;
	grid[center + 1][center + 1] = 1;
	return grid;
}

// print grid to console
void printGrid(const vector<vector<int>> &grid) {
	for (const auto& row : grid) {
		for (const auto& val : row) {
			cout << (val == 0 ? "□" : "■") << " ";
		}
		cout << endl;
	}
}

// count number of living neighbors around a given cell
int countNeighbors(const vector<vector<int>> &grid, int row, int col) {
	int size = grid.size();
	int neighbors = 0;
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			
			// only look for neighbors that are in the bounds of the grid
			// and also make sure to not count the given cell as a neighbor
			if (i >= 0 && i < size && j >= 0 && j < size && (i != row || j != col)) {
				neighbors += grid[i][j];
			}
		}
	}
	return neighbors;
}

// update entire grid to next generation of Game of Life
void nextGen(vector<vector<int>> &grid) {

	// create a new grid that will overwrite the original
	int size = grid.size();
	vector<vector<int>> gridNext = createGrid(size);

	// use the cells of the original grid to compute the new grid
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			// count living neighbors for current cell
			int neighbors = countNeighbors(grid, i, j);
			
			// check if living cell should continue or die
			if (grid[i][j] == 1) {
				gridNext[i][j] = neighbors < 2 || neighbors > 3 ? 0 : 1;
			}
			// check if dead cell should become alive
			else if (neighbors == 3) {
				gridNext[i][j] = 1;
			}
		}
	}

	// new grid overwrites the original grid
	grid = gridNext;
}

// program entry point
int main() {

	// create grid
	vector<vector<int>> grid = createGliderGrid();

	// variables for console interface
	string gameState = "menu"; // "menu", "auto", or "manual"
	int gen = 0;
	string title = "Game of Life, generation ";

	// initial prompt
	cout << "Welcome to the Game of Life! Type one of the following commands to start:\n"
		<< "'auto': auto-play the game\n"
		<< "'manual': manually play the game\n"
		<< "'exit': exit the game\n";

	while (true) {

		// await user input for menu or manual play
		if (gameState == "menu" || gameState == "manual") {
			string input;
			getline(cin, input);

			// exit game using 'exit' command
			if (input == "exit" || input == "e") {
				cout << "Goodbye!\n";
				break;
			}
			// menu options
			else if (gameState == "menu") {
				if (input == "auto" || input == "manual") {
					gameState = input;
				}
				else {
					cout << "Command not recognized. Try 'auto', 'manual', or 'exit'.\n";
				}
			}
		}

		// if we are actually playing the game...
		if (gameState == "auto" || gameState == "manual") {

			// calculate next gen and print it to the console
			gen++;
			cout << title << gen << endl;
			nextGen(grid);
			printGrid(grid);

            // end game after 50 generations
			if (gen >= 50) {
				cout << "Game of Life ended after 50 generations.\n";
				break;
			}

			// prompt user to manually activate next gen
			if (gameState == "manual") {
				cout << "Press Enter to see the next generation. Type 'exit' to exit the game.\n";
			}

			// autoplay by sleeping thread for some time
			if (gameState == "auto") {
				this_thread::sleep_for(chrono::milliseconds(200));
			}
		}
	}
	
	return 0;
}