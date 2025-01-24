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

int main() {
    
    // create grid
	vector<vector<int>> grid = createGliderGrid();

    printGrid(grid);

    return 0;
}