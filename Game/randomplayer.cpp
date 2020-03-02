/*
 * randomplayer.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: raphael
 */

#include <cstdlib>

#include "randomplayer.hpp"
#include "game.hpp"

using namespace std;

Spiel RandomPlayer::vote(GameSituation sit) {
	Spiel spiel;
	if (rand() >= RAND_MAX / 2) {
		spiel.type = Sauspiel;
		spiel.farbe = EICHEL;
	} else {
		spiel.type = None;
	}
	return spiel;
}

Card RandomPlayer::placeCard(vector<Card> possibleCards) {
	int idx = (double) rand() * possibleCards.size() / RAND_MAX;
	return possibleCards[idx];
}
