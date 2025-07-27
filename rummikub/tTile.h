#ifndef tTile_h
#define tTile_h

#include "tColor.h"

const int NUM_TILES = 13;			// between 8 - 13	
const int INITIAL_TILES = 14;		// between 6 - 14
const int MAX_TILES = 50;

struct tTile {
	int number = -1;
	tColor color = NONE;
};

typedef tTile* tTilePtr;

bool operator==(tTile left, tTile right);
void display(tTile tile);

#endif