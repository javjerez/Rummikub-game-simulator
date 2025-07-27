// JAVIER JEREZ REINOSO - RUMMIKUB, FINAL VERSION
// GROUP I

// #define _CRTDBG_MAP_ALLOC

#include <iostream>
// #include <crtdbg.h>
#include <cstdlib>
#include <ctime>

#ifdef _MSC_VER
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

using namespace std;

#include "tColor.h"
#include "tTile.h"
#include "tRack.h"
#include "tRacks.h"
#include "tBag.h"
#include "tSet.h"
#include "tBoard.h"

// PROTOTYPES
int menu();

int main() {			// WE ASSUME FRIENDLY USER !!! -> NO letters or strings introduced
	tBag bag;
	tBoard board;
	tRacks racks;
	int option, player, player_winner, final_counter = 0;
	bool finish = false, winner = false, played, exit = false;
	tTile steal_tile;

	srand(time(NULL));			// random_number = rand() % n; between 0 ... n-1

	createBag(bag);
	display(bag);
	cout << endl << "Press to continue...";
	cin.get();

	deal(bag, racks);
	display(bag);
	cout << endl << "Press to continue...";
	cin.get();

	player = rand() % NUM_PLAYERS;			// random number between 0 and NUM_PLAYERS - 1 -> 3 (since player is an index, it is OK between 0-3)

	while (!winner && !exit) {
		cout << endl << endl << "Turn for player " << player + 1 << "..." << endl;
		display(board);
		finish = false;
		played = false;
		
		while (!finish) {
			cout << endl << "Rack: ";		// We show the rack...
			display(racks[player]);

			option = menu();
			switch (option) {
			case 1:
				sortByNumber(racks[player]);
				break;
			case 2:
				sortByColor(racks[player]);
				break;
			case 3:
				cout << endl << "Possible groups: " << endl;
				displayGroups(racks[player]);
				cout << endl << "Possible runs: " << endl;
				displayRuns(racks[player]);
				break;
			case 4:
				if (play(board, racks[player])) {
					played = true;
					final_counter = 0;
					display(board);
				}

				if (racks[player].counter == 0) {
					winner = true;
					finish = true;
					player_winner = player;
				}

				break;
			case 5:
				if (!played && (bag.counter > 0)) {					// This means that the player did not put any tile in the board...
					steal_tile = getTile(bag);						// The player steals a tile...
					newTile(racks[player], steal_tile);
					cout << endl << "A tile was picked...";
				}
				else if (!played && (bag.counter == 0)) {
					cout << endl << "There are no tiles in the bag, thus the player won't get a new tile!" << endl;
					final_counter++;
					if (final_counter == NUM_PLAYERS) {				// If this counter reaches NUM_PLAYERS, then all the players have pressed option 5 in a row, -> They can't make any move	
						cout << endl << endl << "There are no tiles in the bag and the players can't make any move..." << endl;
						cout << endl << "Hence, the player with lower points wins the game..." << endl;
						player_winner = lowest(racks);
						winner = true;
					}
				}

				player++;											// We change to the next player...
				if (player == NUM_PLAYERS) {
					player = 0;
				}
				finish = true;

				break;
			case 0:
				finish = true;
				exit = true;
				break;
			}
		}
	}

	if (!exit) {
		cout << endl << "The winner is player " << player_winner + 1 << ", congratulations!" << endl;
		cout << endl << "Thank you for playing!" << endl;
	}
	else {
		cout << endl << "You exit the program successfully!" << endl;
	}

	// We free the dynamic memory used in the program...

	deleteBag(bag);				// We will free the dynamic memory used by the tiles remaining in the bag...
	deleteRacks(racks);			// We will free the dynamic memory used by every player's rack...
	deleteBoard(board);			// We will free the dynamic memory used by the sets in the board...


	#ifdef _MSC_VER
		_CrtDumpMemoryLeaks();
	#endif

	// _CrtDumpMemoryLeaks();		// To check memory leaks...

	return 0;		// Put the breakpoint to check memory leaks...
}

int menu() {
	int option = 0;

	do {
		cout << endl << "1: SortByNumber, ";
		cout << "2: SortByColor, ";
		cout << "3: SetsInRack, ";
		cout << "4: PlaceTiles, ";
		cout << "5: Next, ";
		cout << "0: Exit >>> ";
		cin >> option;

		if ((option < 0) || (option > 5)) {
			cout << endl << "ERROR: That is not a valid option!" << endl;
		}

	} while ((option < 0) || (option > 5));


	return option;
}
