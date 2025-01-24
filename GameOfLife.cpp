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

int main() {
    
    // create grid
	vector<vector<int>> grid = createGliderGrid();

    printGrid(grid);

    return 0;
}