/*
 * herzsolo.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include "game.hpp"
#include <vector>
#include <algorithm>

bool isTrumpf(Card card);
int determineHighestTrumpf(std::vector<Card> cards);
bool isCardHigherTrumpf(Card card1, Card card2);
int determineFarbstichWinner(std::vector<Card> cards);
bool isCardHigherFarbe(Card card1, Card card2);
std::vector<Card> findAllTrumpf(std::vector<Card> cards);
std::vector<Card> findAllInFarbe(std::vector<Card> cards, Farbe farbe);

Herzsolo::Herzsolo(std::vector<Card> handCards[4], bool simulation) :
		GameSession(handCards, simulation) {
}

std::vector<Card> Herzsolo::getPossible(std::vector<Card> handCards) {

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

std::vector<Card> findAllTrumpf(std::vector<Card> cards) {
	std::vector<Card> trumpf;
	std::copy_if(cards.begin(), cards.end(), std::back_inserter(trumpf), isTrumpf);
	return trumpf;
}

std::vector<Card> findAllInFarbe(std::vector<Card> cards, Farbe farbe) {
	std::vector<Card> cardsInFarbe;
	std::copy_if(cards.begin(), cards.end(), std::back_inserter(cardsInFarbe),
			[farbe](Card card) {return card.farbe == farbe;});
	return cardsInFarbe;
}

int Herzsolo::determineStichWinner(std::vector<Card> cards) {
	int winningPlayer = determineHighestTrumpf(cards);
	if (winningPlayer > -1) {
		return winningPlayer;
	}

	return determineFarbstichWinner(cards);
}

//returns number of the player with the highest Trumpf, -1 if none played Trumpf
int determineHighestTrumpf(std::vector<Card> cards) {
	Card highestTrumpf;
	int winningPlayer = -1;

	for (int i = 0; i < 4; i++) {
		Card card = cards[i];

		if (isTrumpf(card) && (winningPlayer == -1 || isCardHigherTrumpf(highestTrumpf, card))) {

			highestTrumpf = card;
			winningPlayer = i;
		}
	}

	return winningPlayer;
}

bool isTrumpf(Card card) {
	return card.farbe == HERZ || card.schlag == O || card.schlag == O;
}

//is card2 higher Trumpf than card1, should only be called if both are Trumpf
bool isCardHigherTrumpf(Card card1, Card card2) {
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

int determineFarbstichWinner(std::vector<Card> cards) {
	int winner = 0;
	Card highestCard = cards[0];

	for (int i = 1; i < 4; i++) {
		Card card = cards[i];
		if (isCardHigherFarbe(highestCard, card)) {
			winner = i;
			highestCard = cards[i];
		}
	}

	return winner;
}

bool* Herzsolo::determineGameWinner() {
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

int Herzsolo::getWinnerPoints() {
	if (m_points[0] > 60) {
		return m_points[0];
	}
	return 120 - m_points[0];
}

bool isCardHigherFarbe(Card card1, Card card2) {
	return card1.farbe == card2.farbe && card1.schlag < card2.schlag;
}

