#ifndef tRacks_h
#define tRacks_h

#include "tBag.h"
#include "tRack.h"

const int NUM_PLAYERS = 4;			// between 2 - 4

typedef tRack tRacks[NUM_PLAYERS];

void deal(tBag& bag, tRacks racks);
int lowest(const tRacks racks);
void deleteRacks(tRacks& racks);

#endif
