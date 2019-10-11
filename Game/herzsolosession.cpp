/*
 * herzsolo.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include <vector>

#include "game.hpp"

HerzsoloSession::HerzsoloSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation) :
		GameSession(handCards, common, simulation) {
}

std::vector<Card> HerzsoloSession::getPossible(std::vector<Card> handCards) {

	if (getOpenCards().empty()) {
		return handCards;
	}

	Card firstCard = getOpenCards().front();
	if (isTrumpf(firstCard)) {
		std::vector<Card> trumpf = findAllTrumpf(handCards);
		if (!trumpf.empty()) {
			return trumpf;
		}
		return handCards;
	}

	std::vector<Card> cardsInFarbe = findAllInFarbe(handCards, firstCard.farbe);
	if (!cardsInFarbe.empty()) {
		return cardsInFarbe;
	}
	return handCards;
}

bool HerzsoloSession::isTrumpf(Card card) {
	return card.farbe == HERZ || card.schlag == O || card.schlag == U;
}

//is card2 higher Trumpf than card1, should only be called if both are Trumpf
bool HerzsoloSession::isCardHigherTrumpf(Card card1, Card card2) {
	if (card1.schlag == O) {
		if (card2.schlag == O && card1.farbe < card2.farbe) {
			return true;
		} else {
			return false;
		}
	} else if (card1.schlag == U) {
		return card2.schlag == O || (card2.schlag == U && card1.farbe < card2.farbe);
	} else if (card2.schlag == O || card2.schlag == U) {
		return true;
	} else {
		return card1.schlag < card2.schlag;
	}
}

bool* HerzsoloSession::determineGameWinner() {
	bool* winner = new bool[4];
	if (getPoints()[0] > 60) {
		winner[0] = true;
		winner[1] = false;
		winner[2] = false;
		winner[3] = false;
	} else {
		winner[0] = false;
		winner[1] = true;
		winner[2] = true;
		winner[3] = true;
	}
	return winner;
}

