/*
 * main.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include "Game/game.hpp"
#include "SimulationTree/treebuilder.hpp"
#include "Game/shuffler.hpp"

#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>

#define OPTIONS_P1 735471
#define OPTIONS_P2 12870

void prepareCardSelection(uint8_t* possibleSelections, int nOptions);
void writePossibleSelection(uint8_t* selection, uint8_t* possibleSelections);
void chooseCard(uint8_t* selection, int idx, uint8_t* possibleSelections);

int main() {
	/*uint8_t* possibleSelectionsP1 = new uint8_t[OPTIONS_P1 * 8];
	 prepareCardSelection(possibleSelectionsP1, 24);
	 uint8_t* possibleSelectionsP2 = new uint8_t[OPTIONS_P2 * 8];
	 prepareCardSelection(possibleSelectionsP2, 16);*/
	int selectionP0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	std::vector<Card> cardsP0 = Shuffler().provideCards(selectionP0);
	std::vector<Card> handCards_dummy[4];
	unsigned long combs = TreeBuilder(new Herzsolo(handCards_dummy,true)).countCombs(cardsP0);
	std::cout << combs << std::endl;
	return 0;
}

void prepareCardSelection(uint8_t* possibleSelections, int nOptions) {
	uint8_t selection[8];
	for (int i = 0; i <= nOptions - 8; i++) {
		selection[0] = i;
		chooseCard(selection, 1, possibleSelections);
	}

}

void chooseCard(uint8_t* selection, int idx, uint8_t* possibleSelections) {
	if (idx == 8) {
		writePossibleSelection(selection, possibleSelections);
	} else {
		for (int i = selection[idx - 1] + 1; i < 24; i++) {
			selection[idx] = i;
			chooseCard(selection, idx + 1, possibleSelections);
		}
	}
}

void writePossibleSelection(uint8_t* selection, uint8_t* possibleSelections) {
	static int pos = 0;
	memcpy(&possibleSelections[pos * 8], selection, 8);
	pos++;
}

