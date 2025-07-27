#include "tBag.h"
#include <iostream>
#include <iomanip>

using namespace std;

void createBag(tBag& bag) {
	tTile aux_tile;

	for (int row = 0; row < BAG_ROWS; row++) {
		for (int col = 0; col < NUM_TILES; col++) {
			aux_tile.number = col + 1;
			aux_tile.color = tColor(row % 4);					// We use an auxiliar tile to get the value of the created tile (number and color)

			bag.tiles[row][col] = new tTile(aux_tile);			// we create the tile with the auxiliar value in dynamic memory

			bag.counter++;
		}
	}
}

void display(tBag bag) {
	for (int row = 0; row < BAG_ROWS; row++) {
		for (int col = 0; col < NUM_TILES; col++) {
			if (bag.tiles[row][col] == NULL) {
				cout << setw(4) << "-1";
			}
			else {
				display(*bag.tiles[row][col]);
			}
		}
		cout << endl;
	}
}

tTile getTile(tBag& bag) {
	tTile chosen_tile;
	int row, column;

	if (bag.counter > 0) {									// There are available tiles
		row = rand() % BAG_ROWS;
		column = rand() % NUM_TILES;

		while (bag.tiles[row][column] == NULL) {			// If the tile is not available... (pointer is pointing to NULL)
			column++;
			if (column == NUM_TILES) {						// If we reach the end of columns
				row++;
				column = 0;

				if (row == BAG_ROWS) {						// If we reach the end of rows
					row = 0;
				}
			}
		}

		chosen_tile = *bag.tiles[row][column];				// We equal chosen_tile to the value in the address of bag.tiles[row][column]

		delete bag.tiles[row][column];						// We delete that tile in the bag from the dynamic memory...
		bag.tiles[row][column] = NULL;						// Then we point the tile in the bag to NULL, so it cannot be selected again

		bag.counter--;										// We reduce the bag counter everytime we get a tile...
	}

	return chosen_tile;
}

void deleteBag(tBag& bag) {
	for (int row = 0; row < BAG_ROWS; row++) {
		for (int col = 0; col < NUM_TILES; col++) {
			if (bag.tiles[row][col] != NULL) {
				delete bag.tiles[row][col];					// We will free the dynamic memory used by the tiles (remaining in the bag)
			}
		}
	}
	bag.counter = 0;
}
