#include "tColor.h"
#include <iostream>

using namespace std;

void textColor(tColor color) {
	switch (color) {
	case YELLOW:
		cout << "\033[1;40;33m";
		break;
	case BLUE:
		cout << "\033[40;34m";
		break;
	case RED:
		cout << "\033[40;31m";
		break;
	case GREEN:
		cout << "\033[40;32m";
		break;
	case WHITE:
		cout << "\033[40;37m";
		break;
	}
}