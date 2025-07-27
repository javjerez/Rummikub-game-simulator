#include "tRack.h"
#include "tSet.h"
#include <iostream>

using namespace std;

void sortByNumber(tRack& rack) {
	int lowest;
	tTile tmp;

	for (int i = 0; i < rack.counter - 1; i++) {		// We put the -1 because the last tile (tile left) will be sorted automatically
		lowest = i;
		for (int m = i + 1; m < rack.counter; m++) {	// m = i + 1, because previous tiles to i are already sorted
			if (rack.tiles[m].number < rack.tiles[lowest].number) {
				lowest = m;
			}
		}
		tmp = rack.tiles[i];							// We swap with an auxiliar variable
		rack.tiles[i] = rack.tiles[lowest];
		rack.tiles[lowest] = tmp;
	}
}

void sortByColor(tRack& rack) {
	int lowest;
	tTile tmp;

	for (int i = 0; i < rack.counter - 1; i++) {
		lowest = i;
		for (int m = i + 1; m < rack.counter; m++) {
			if (int(rack.tiles[m].color) < int(rack.tiles[lowest].color)) {
				lowest = m;
			}
		}

		if (lowest > i) {
			tmp = rack.tiles[i];
			rack.tiles[i] = rack.tiles[lowest];
			rack.tiles[lowest] = tmp;
		}
	}
	
	for (int i = 0; i < rack.counter - 1; i++) {			// We put the -1 because the last tile (tile left) will be sorted automatically
		lowest = i;
		for (int m = i + 1; m < rack.counter; m++) {		// m = i + 1, because previous tiles to i are already sorted
			if ((rack.tiles[m].number + int(rack.tiles[m].color * NUM_TILES)) < (rack.tiles[lowest].number + int(rack.tiles[lowest].color * NUM_TILES))) {
				lowest = m;
			}
		}
		tmp = rack.tiles[i];						// We swap with an auxiliar variable
		rack.tiles[i] = rack.tiles[lowest];
		rack.tiles[lowest] = tmp;
	}
	
}

void display(tRack rack) {
	for (int i = 0; i < rack.counter; i++) {
		display(rack.tiles[i]);
	}
}

void displayGroups(tRack rack) {				// group: 3 - 4 tiles, same number BUT different colours
	int pos = 0, counter = 0;
	tSet group, find_set, aux;
	tTile aux_tile;
	bool found = false;

	sortByNumber(rack);							// First we sort the list by number...

	while (pos < rack.counter - 2) {			// The last 2 can't be a group...
		counter = 0;							// Each time we start from the beginning of the set

		group = new tNode;						// This is our first node of the new_group (first tile)
		group->tile = rack.tiles[pos];
		aux_tile = group->tile;					// We save the tile in that position in an auxiliar tile and move to the next node | aux_tile equals previous node
		group->next = NULL;						// It is very important that the last node always has NULL in its field next !!!

		aux = group;

		counter++;
		pos++;

		while ((pos < rack.counter) && (rack.tiles[pos].number == aux_tile.number)) {		// We compare it to aux_tile (rack.tiles[pos].number == group[counter - 1].number)
			found = false;

			int i = 0;
			while ((i < counter) && (!found)) {
				find_set = find(group, rack.tiles[pos]);
				if (find_set != NULL) {						// If idx is not equal to -1, we have found the same tile in the set
					found = true;
				}
				else {
					i++;
				}
			}

			if (!found) {									// If not found, the tile is not repeated in the set
				aux->next = new tNode;						// If not found, we create the next node
				aux = aux->next;
				aux->tile = rack.tiles[pos];
				aux->next = NULL;							// It is very important that the last node always has NULL in its field next !!!

				counter++;									// A new node was added to the group...
			}
			pos++;
		}

		if (counter > 2) {									// If there are 3 or more tiles in the set...
			display(group);
			cout << endl;
		}
		cleanSet(group);									// We delete the group once displayed or if not used
	}
}

void displayRuns(tRack rack) {
	int pos = 0, counter = 0;
	tSet run, find_set, aux;
	bool found = false;

	sortByColor(rack);						// First we sort the list by color...

	while (pos < rack.counter - 2) {		// The last 2 can't be a group...
		counter = 0;						// Each time we start from the beginnig of the set

		run = new tNode;					// We create the new node
		run->tile = rack.tiles[pos];		// The set run is in the first node since we have just created it
		run->next = NULL;

		aux = run;

		counter++;
		pos++;

		while ((pos < rack.counter) && (rack.tiles[pos].color == rack.tiles[pos - 1].color) &&
			((rack.tiles[pos].number == rack.tiles[pos - 1].number + 1) || (rack.tiles[pos].number == rack.tiles[pos - 1].number))) {
			found = false;

			int i = 0;
			while ((i < counter) && (!found)) {
				find_set = find(run, rack.tiles[pos]);

				if (find_set != NULL) {					// If find_set is not equal to NULL, we have found the same tile in the set
					found = true;
				}
				else {
					i++;
				}
			}

			if (!found) {
				aux->next = new tNode;					// If not found, the tile is not repeated in the set
				aux = aux->next;						// If not found, we create the next node
				aux->tile = rack.tiles[pos];
				aux->next = NULL;						// It is very important that the last node always has NULL in its field next !!!

				counter++;								// The counter does the same as the run->next, but with numbers
			}
			pos++;
		}

		if (counter > 2) {								// If there are 3 or more tiles in the set (the counter starts in 0)...
			display(run);
			cout << endl;
		}
		cleanSet(run);									// We delete the run once displayed or if not used
	}
}

void initRack(tRack& rack) {					// creating a dynamic array for 8 tiles...
	rack.tiles = new tTile[rack.capacity];				// We create the dynamic array with its current capacity (8 when initialized)
}

void newTile(tRack& rack, tTile newTile) {
	// will add a tile to a rack by previously increasing the capacity of the list if the dynamic array is full...
	int old_capacity = 0, old_counter = 0;
	tTilePtr aux;

	if (rack.capacity == rack.counter) {			// We create a new dynamic array with 8 more elements if the DYNAMIC ARRAY IS FULL
		rack.capacity += MORE_CAPACITY;
		aux = new tTile[rack.capacity];				// We create the new dynamic array with the new capacity

		for (int i = 0; i < rack.counter; i++) {
			aux[i] = rack.tiles[i];					// We copy the old dynamic array in the new dynamic array
		}

		old_counter = rack.counter;
		old_capacity = rack.capacity;

		deleteRack(rack);							// We delete the old rack (the old array)
			
		rack.counter = old_counter;
		rack.capacity = old_capacity;
		rack.tiles = aux;							// We point the rack to the auxiliar array
	}

	rack.tiles[rack.counter] = newTile;				// We introduce the newTile in the dynamic array
	rack.counter++;
}

void deleteRack(tRack& rack) {						// We free the dynamic memory used by a rack...
	delete[] rack.tiles;
	rack.capacity = 0;
	rack.counter = 0;
}
