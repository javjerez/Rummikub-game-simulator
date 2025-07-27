#include "tTile.h"
#include <iostream>
#include <iomanip>

using namespace std;

void display(tTile tile) {
	textColor(tile.color);
	cout << setw(4) << tile.number;
	textColor(WHITE);
}

bool operator==(tTile left, tTile right) {
	return (left.color == right.color) && (left.number == right.number);
}