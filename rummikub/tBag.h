#ifndef tBag_h
#define tBag_h

#include "tTile.h"

const int BAG_ROWS = 2 * NUM_COLORS;

typedef tTile* tTilePtr;

typedef tTilePtr tBagArray[BAG_ROWS][NUM_TILES];	// We declare the static bi-dimensional array of pointers with dynamic data...

struct tBag {
	tBagArray tiles;
	int counter = 0;								// We initialize the counter to 0
};

void createBag(tBag& bag);							// Creates all tiles in dynamic memory...
tTile getTile(tBag& bag);							// Will get a tile from the bag
void display(tBag bag);
void deleteBag(tBag& bag);							// Used at the end of the program

#endif
