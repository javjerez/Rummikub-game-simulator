#include "tSet.h"
#include <iostream>

using namespace std;

// do not use const! tSet is a pointer !!!
void display(tSet set) {
	tSet aux = set;

	while (aux != NULL) {			// While the auxiliar pointer is not NULL, we display the tile of that node and move to the next one
		display(aux->tile);
		aux = aux->next;
	}
}

// use tSet& set. If not, the argument will not be assigned NULL !!!
void cleanSet(tSet& set) {														// We clean the set...
	tSet aux = set;

	while (set != NULL) {					// We delete the dynamic nodes of the run...
		aux = set;
		set = set->next;
		delete aux;
	}
}

// remove const. If not found, aux is always NULL
tSet find(tSet set, tTile tile) {
	tSet aux = set;
	bool found = false;

	while ((!found) && (aux != NULL)) {
		if (aux->tile == tile) {
			found = true;					// The same node tile was found, so we return the pointer to the node
		}
		else {
			aux = aux->next;
		}
	}
	// Returns a NULL pointer if the tile was not found

	return aux;
}

void removeTiles(tRack& rack, tSet set) {
	int index = 0, new_counter = 0, new_capacity = 0;
	tSet aux = set;
	bool found = false;
	tTilePtr auxiliarArray;

	while (aux != NULL) {
		index = 0;
		found = false;

		while ((index < rack.counter) && (!found)) {	
			if (aux->tile == rack.tiles[index]) {			// We find position of the node in the linked_list
				found = true;
			}
			else {
				index++;
			}
		}

		// we delete it from the rack
		rack.tiles[index] = rack.tiles[rack.counter - 1];	// We exchange the tiles to erase the one found
		rack.counter--;

		// If there are 8 unused positions...
		if (rack.capacity == rack.counter + 8) {			// There are 8 unused positions, so we delete 4 of them
			
			auxiliarArray = new tTile[rack.capacity - 4];	// We create the auxiliar dynamic array with the new capacity
			new_counter = rack.counter;
			new_capacity = rack.capacity - 4;

			for (int i = 0; i < rack.counter; i++) {
				auxiliarArray[i] = rack.tiles[i];			// We copy the values of old rack in the new (auxiliar) array
			}

			deleteRack(rack);								// We delete the old dynamic array
			rack.capacity = new_capacity;					// We update the rack capacity
			rack.counter = new_counter;						// We update the rack counter, it was deleted in the deleteRack()
			
			rack.tiles = auxiliarArray;						// We point the rack to the auxiliar array
			
		}
		aux = aux->next;				// We move to the next node in order to the delete that tile from the rack
	}
}

int newSet(tRack rack, tSet& set) {
	int number_of_tiles = 0, aux_position;
	bool is_position_valid = true;
	tSet aux = set;											// We initialize the auxiliar set to the set...

	cout << endl << "Tiles (0 at the end): ";				// We ask for the tiles that we want to introduce in the set
	cin >> aux_position;

	while (aux_position != 0) {
		// If we introduce an index bigger than the rack.counter, we would be selecting an inexistent position -> Impossible...
		if (aux_position > rack.counter) {
			is_position_valid = false;
		}
		else {		// If it is a valid index, then we continue with the program

			if (set == NULL) {				// Empty set... (The first one)
				set = new tNode;								// If the set is null, we create the a new node in the dynamic memory
				set->tile = rack.tiles[aux_position - 1];		// We subtract 1 number to the index selected by the user
				set->next = NULL;								// We point the last node to NULL...
				aux = set;
			}
			else {							// If set != NULL
				aux->next = new tNode;							// From the last node, we create a new one and add the tile to the new last node
				aux = aux->next;								// We move to the last node...
				aux->tile = rack.tiles[aux_position - 1];		// We subtract 1 number to the index selected by the user
				aux->next = NULL;								// We point the last node to NULL
			}

			number_of_tiles++;
		}
		cin >> aux_position;
	}

	if (!is_position_valid) {
		number_of_tiles = -1;
	}

	return number_of_tiles;
}

bool placeTile(tSet& set, tTile tile) {
	// int value = 0;
	bool is_placed;
	tSet findSet, initialNode, lastNode, aux;

	initialNode = set;
	lastNode = set;
	while (lastNode->next != NULL) {						// In this while we get the last tile of the set
		lastNode = lastNode->next;
	}

	findSet = find(set, tile);
	if (findSet != NULL) {						// findSet != NULL means the tile was found in the set
		is_placed = false;						// The tile is already in the set...
	}
	else {
		aux = new tNode;
		aux->tile = tile;
		aux->next = NULL;

		if ((tile.number == initialNode->tile.number) && (tile.number == lastNode->tile.number)) {		// It is a group
			lastNode->next = aux;							// the following node to the last is the axiliar set with the new tile
			aux->next = NULL;								// The next node will be null (aux is the new last node)
			is_placed = true;
		}
		else if ((tile.color == initialNode->tile.color) && (tile.number == initialNode->tile.number - 1) && (tile.color == lastNode->tile.color)) {	// It is a run from the left
			aux->next = set;
			set = aux;
			is_placed = true;
		}
		else if ((tile.color == lastNode->tile.color) && (tile.number == lastNode->tile.number + 1) && (initialNode->tile.color == tile.color)) {	// It is a run from the right
			lastNode->next = aux;							// the following node to the last is the axiliar set with the new tile
			aux->next = NULL;								// The next node will be null (aux is the new last node)
			is_placed = true;
		}
		else {
			is_placed = false;
			deleteSet(aux);									// We delete the set that was initially created since we did not need it...
		}
	}

	return is_placed;
}

// the copy must have its own nodes! (the set will not be empty)
void copy(tSet set, tSet& cp) {
	tSet aux_set, aux_cp;									//  creates a copy of one set into another (cp). You will need to create copies of the nodes for the second set

	if (set == NULL) {										// If the set has no nodes, then the copy neither
		cp = NULL;
	}
	else {
		cp = new tNode;
		cp->tile = set->tile;
		cp->next = NULL;

		aux_set = set;
		aux_cp = cp;

		while (aux_set->next != NULL) {
			aux_set = aux_set->next;						// We move to the next node once we know that aux_set->next is not NULL
			aux_cp->next = new tNode;
			aux_cp = aux_cp->next;							// We move to the next aux_copy node we just created
			aux_cp->tile = aux_set->tile;
			aux_cp->next = NULL;
		}
	}
}

void deleteSet(tSet& set) {			// frees the dynamic memory used by the linked list
	tSet aux;

	while (set != NULL) {
		aux = set;
		set = set->next;
		delete aux;
	}
}

