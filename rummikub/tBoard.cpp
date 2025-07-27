#include "tBoard.h"
#include <iostream>
#include <iomanip>

using namespace std;

void addSet(tBoard& board, tSet set) {
	if (board.counter < MAX_SETS) {
		copy(set, board.sets[board.counter]);
		board.counter++;
	}
	else {
		cout << endl << "ERROR: There is no more space in the board!" << endl;
	}
}

bool play(tBoard& board, tRack& rack) {
	int number_of_tiles, set_position, i = 0, jug, value, j = 0;
	tSet setToPlace = NULL, setToPlace_aux;							// We initialize the the setToPlace set (auxiliar set) to NULL
	bool is_placed = false, is_group = false, is_run = false;
	tBoard aux_board;

	cout << endl << "Rack: ";
	display(rack);
	displayPositions(rack.counter);
	number_of_tiles = newSet(rack, setToPlace);						// The new set will be loaded in setToPlace

	if (number_of_tiles != -1 && number_of_tiles != 0) {
		cout << endl << "Set: ";
		display(setToPlace);
	}

	if (number_of_tiles == 1) {										// If there is only one tile...
		setToPlace_aux = setToPlace;

		cout << endl << "Sets on the board where the tile can be placed: ";
		number_of_tiles = 0;

		for (int i = 0; i < board.counter; i++) {
			copy(board.sets[i], aux_board.sets[i]);
		}
		aux_board.counter = board.counter;

		for (int i = 0; i < aux_board.counter; i++) {
			if (placeTile(aux_board.sets[i], setToPlace_aux->tile)) {
				number_of_tiles++;
				if (number_of_tiles > 1) {
					cout << ", ";
				}
				cout << j + 1;
				jug = i;
			}
			j++;
		}

		if (number_of_tiles == 0) {
			cout << "None! Try again..." << endl;
			deleteSet(setToPlace);							// If no tile introduced, we delete the setToPlace
		}
		else if (number_of_tiles == 1) {
			cout << "  -> Placed!" << endl;
			placeTile(board.sets[jug], setToPlace_aux->tile);
			is_placed = true;
		}
		else {
			// Here we use a do-while in order to ask the user a set until the input is one of the valid sets
			do {
				cout << endl << "Select in which set do you want to place the tile: ";
				cin >> set_position;

				if (!placeTile(board.sets[set_position - 1], setToPlace_aux->tile)) {
					cout << endl << "ERROR: That is not a valid set! Try again..." << endl;
				}
				else {
					cout << "  -> Placed!" << endl;
					is_placed = true;
				}
			} while (!is_placed);
		}
		deleteBoard(aux_board);								// We will free the dynamic memory used by the sets in the auxiliar board...
	}
	else if (number_of_tiles > 2) {							// If there are more than two tiles...
		tSet setToPlace_prev;

		setToPlace_prev = setToPlace;						// -> k index
		setToPlace_aux = setToPlace;						// -> i index
		
		i = 0;												// We set the i to 1 in order to compare the number of each tile with the previous one...
		is_group = true;
		value = setToPlace_aux->tile.number;				// The first number of the set...

		while ((is_group) && (i < number_of_tiles)) {
			int k = 0;
			setToPlace_prev = setToPlace;
			while ((k < number_of_tiles) && (is_group) && (setToPlace_aux->tile.number == value)) {
				if ((setToPlace_aux->tile.color == setToPlace_prev->tile.color) && (i == k)) {			// It is the same tile...
					k++;
					setToPlace_prev = setToPlace_prev->next;
				}
				else if ((setToPlace_aux->tile.color != setToPlace_prev->tile.color) && (i != k)) {
					k++;
					setToPlace_prev = setToPlace_prev->next;
				}
				else {
					is_group = false;
				}
			}

			if (setToPlace_aux->tile.number != value) {		// If we got out of the while because of this condition, it will not be a group...
				is_group = false;
			}

			if (is_group) {
				i++;
				setToPlace_aux = setToPlace_aux->next;
			}
		}

		if (!is_group) {									// If it is not a group, then we check if it is a run...
			i = 1;
			setToPlace_aux = setToPlace;					// -> i index
			setToPlace_prev = setToPlace;					// -> i index, but 'i' will be the previous node to setToPlace_aux
			setToPlace_aux = setToPlace_aux->next;			// Since i = 1, then we have to move to the next node from the initial node

			is_run = true;
			while (is_run && i < number_of_tiles) {

				if ((setToPlace_aux->tile.color == setToPlace_prev->tile.color) &&
					((setToPlace_aux->tile.number == setToPlace_prev->tile.number + 1))) {
					i++;
					setToPlace_aux = setToPlace_aux->next;
					setToPlace_prev = setToPlace_prev->next;
				}
				else {
					is_run = false;
				}
			}
		}

		if (!is_run && !is_group) {
			cout << "  - It is not a valid set!" << endl;
			cleanSet(setToPlace);								// If the set introduced is not valid, we delete it
		}
		else if (is_group) {
			cout << "  - Valid group!" << endl;
		}
		else {
			cout << "  - Valid run!" << endl;
		}

		if (is_group || is_run) {
			addSet(board, setToPlace);
			is_placed = true;
		}
	}
	else if (number_of_tiles == -1) {
		cout << endl << "ERROR: You entered an invalid position!" << endl;
		deleteSet(setToPlace);
	}
	else if (number_of_tiles == 0) {
		cout << endl << "ERROR: No tiles selected! Try again..." << endl;
	}
	else {		// Other cases, e.g: 2
		cout << endl << "ERROR: An error occured!" << endl;
		deleteSet(setToPlace);						// We delete the set
	}

	if (is_placed) {
		removeTiles(rack, setToPlace);				// We remove the tiles of the new set from the rack, (it also updates the rack.counter)
		deleteSet(setToPlace);						// We do not need the setToPlace set any more, and since we have copied it in the board, we can delete it
	}

	return is_placed;
}

void display(tBoard board) {
	cout << endl << "Board: " << endl;
	if (board.counter == 0) {
		cout << "No sets" << endl;
	}
	else {
		for (int i = 0; i < board.counter; i++) {
			cout << i + 1 << ":";
			display(board.sets[i]);						// We call display sets...
			cout << endl;
		}
	}
}

void displayPositions(int num) {
	cout << endl << "      ";							// num = rack.counter...
	for (int i = 0; i < num; i++) {
		cout << setw(4) << right << i + 1;
	}
	cout << endl;
}

void deleteBoard(tBoard& board) {
	for (int i = 0; i < board.counter; i++) {
		deleteSet(board.sets[i]);
	}
}
