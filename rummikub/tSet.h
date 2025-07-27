#ifndef tSet_h
#define tSet_h

#include "tRack.h"

struct tNode;
typedef tNode* tSet;

struct tNode {
	tTile tile;
	tSet next;
};

tSet find(tSet set, tTile tile);
void cleanSet(tSet& set);
void removeTiles(tRack& rack, tSet set);
int newSet(tRack rack, tSet& set);
bool placeTile(tSet& set, tTile tile);
void display(tSet set);

void copy(tSet set, tSet& cp);
void deleteSet(tSet& set);

#endif
