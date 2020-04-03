/*
 * gametypes.cpp
 *
 *  Created on: Mar 15, 2020
 *      Author: raphael
 */

#include "Game/gametype.hpp"
#include <stdexcept>
#include "Game/helper.hpp"

using namespace std;

class SauspielType: public GameType {
public:
	vector<Spiel> getPossibleVariants(vector<Card> handCards) {
		vector<Spiel> possibles;
		Card sau;
		sau.schlag = A;
		Spiel spiel;
		spiel.type = GameTypeName::Sauspiel;
		for (Farbe farbe = SCHELLEN; farbe <= EICHEL; farbe = (Farbe) ((int) farbe + 1)) {
			if (farbe != HERZ) {
				sau.farbe = farbe;
				if (!helper::containsCard(handCards, sau) && helper::containsFarbeNotOU(handCards, farbe)) {
					spiel.farbe = farbe;
					possibles.push_back(spiel);
				}
			}
		}
		return possibles;
	}
};

class NoneType: public GameType {
public:
	vector<Spiel> getPossibleVariants(vector<Card> handCards) {
		vector<Spiel> possibles;
		Spiel none;
		none.type = None;
		possibles.push_back(none);
		return possibles;
	}
};

GameType* GameType::gameTypeFromName(GameTypeName name) {
	switch (name) {
	case None:
		return new NoneType();
	case Sauspiel:
		return new SauspielType();
	default:
		throw runtime_error("Selected game type is not defined");
	}
}

GameType::~GameType() {
}

