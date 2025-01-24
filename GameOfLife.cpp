#include <iostream>
#include <vector>

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

int main() {
    
    // create grid
	vector<vector<int>> grid = createGliderGrid();

    // print initial generation
    cout << "gen 0\n";
    printGrid(grid);

    // update generation and print
    nextGen(grid);
    cout << "gen 1\n";
    printGrid(grid);

    // update generation and print
    nextGen(grid);
    cout << "gen 2\n";
    printGrid(grid);

    return 0;
}