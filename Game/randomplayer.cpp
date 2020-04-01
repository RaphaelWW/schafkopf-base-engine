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

Spiel RandomPlayer::vote(GameSituation sit, vector<Spiel> possibleVotes) {
	if (possibleVotes.size() > 1 && rand() >= RAND_MAX / 2) {
		return possibleVotes[1];
	}
	return possibleVotes[0];
}

Card RandomPlayer::placeCard(vector<Card> possibleCards) {
	int idx = (double) rand() * possibleCards.size() / RAND_MAX;
	return possibleCards[idx];
}
