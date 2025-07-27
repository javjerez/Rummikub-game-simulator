#ifndef tRack_h
#define tRack_h

#include "tTile.h"

const int MORE_CAPACITY = 8;

struct tRack {				// RACKS
	tTilePtr tiles;						// Dynamic array
	int counter = 0;
	int capacity = 8;					// Initial capacity of 8 tiles...
};

void sortByNumber(tRack& rack);
void sortByColor(tRack& rack);
void display(tRack rack);
void displayGroups(tRack rack);
void displayRuns(tRack rack);

void initRack(tRack& rack);
void newTile(tRack& rack, tTile newTile);
void deleteRack(tRack& rack);

#endif
