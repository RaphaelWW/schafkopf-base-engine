/*
 * sauspielsession.cpp
 *
 *  Created on: Oct 3, 2019
 *      Author: raphael
 */

#include <vector>

#include "game.hpp"

using namespace std;

bool isTrumpf(Card card);
int determineHighestTrumpf(std::vector<Card> cards);
bool isCardHigherTrumpf(Card card1, Card card2);
int determineFarbstichWinner(std::vector<Card> cards);
bool isCardHigherFarbe(Card card1, Card card2);

SauspielSession::SauspielSession(std::vector<Card>* handCards, Farbe farbe, bool simulation) :
		GameSession(handCards, simulation), m_farbe(farbe) {
}

bool SauspielSession::isTrumpf(Card card) {
	return card.farbe == HERZ || card.schlag == O || card.schlag == O;
}

//is card2 higher Trumpf than card1, should only be called if both are Trumpf
bool SauspielSession::isCardHigherTrumpf(Card card1, Card card2) {
	if (card1.schlag == O) {
		if (card2.schlag == O && card1.farbe < card2.farbe) {
			return true;
		} else {
			return false;
		}
	} else if (card1.schlag == U) {
		return card2.schlag == O || (card2.schlag == U && card1.farbe < card2.farbe);
	} else {
		return card1.schlag < card2.schlag;
	}
}
