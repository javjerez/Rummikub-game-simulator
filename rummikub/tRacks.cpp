#include "tRacks.h"
#include <iostream>

using namespace std;

void deal(tBag& bag, tRacks racks) {
	tTile chosen_tile;

	for (int i = 0; i < NUM_PLAYERS; i++) {
		initRack(racks[i]);								// We call initRack() to create the dynamic array for that player (player's rack)
		for (int j = 0; j < INITIAL_TILES; j++) {		// Here we fill the rack...
			chosen_tile = getTile(bag);
			newTile(racks[i], chosen_tile);				// We call newTile() to introduce the tile got from the bag
		}
	}
}

int lowest(const tRacks racks) {
	int return_index, player_points = 0, min_points = 1000;			// We initialize min_points to a huge number

	cout << endl << "Player's points: " << endl;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		player_points = 0;
		for (int j = 0; j < racks[i].counter; j++) {
			player_points += racks[i].tiles[j].number;
		}

		cout << " - Player " << i + 1 << " points: " << player_points << " points" << endl;

		if (player_points < min_points) {
			min_points = player_points;				// The minimum points now will be the ones of the player...
			return_index = i;						// We save the index of the player with less points...
		}
	}

	return return_index;
}

void deleteRacks(tRacks& racks) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		deleteRack(racks[i]);
	}
}