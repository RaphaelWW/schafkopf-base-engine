/*
 * herzsolo.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include <vector>

#include "game.hpp"

bool isTrumpf(Card card);
int determineHighestTrumpf(std::vector<Card> cards);
bool isCardHigherTrumpf(Card card1, Card card2);
std::vector<Card> findAllTrumpf(std::vector<Card> cards);
std::vector<Card> findAllInFarbe(std::vector<Card> cards, Farbe farbe);

HerzsoloSession::HerzsoloSession(std::vector<Card>* handCards, bool simulation) :
		GameSession(handCards, simulation) {
}

std::vector<Card> HerzsoloSession::getPossible(std::vector<Card> handCards) {

	if(m_openCards.empty()){
		return handCards;
	}

	Card firstCard = m_openCards.front();
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
	return card.farbe == HERZ || card.schlag == O || card.schlag == O;
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
	} else {
		return card1.schlag < card2.schlag;
	}
}

bool* HerzsoloSession::determineGameWinner() {
	bool* winner = new bool[4];
	if (m_points[0] > 60) {
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

int HerzsoloSession::getWinnerPoints() {
	if (m_points[0] > 60) {
		return m_points[0];
	}
	return 120 - m_points[0];
}

