/*
 * shuffler.cpp
 *
 *  Created on: Aug 17, 2019
 *      Author: raphael
 */

#include <cstdlib>

#include"Game/shuffler.hpp"

Shuffler::Shuffler() {
	for (int farbe = SCHELLEN; farbe <= EICHEL; farbe++) {
		for (int schlag = SIEBEN; schlag <= A; schlag++) {
			Card card;
			card.schlag = (Schlag) schlag;
			card.farbe = (Farbe) farbe;
			m_availableCards.push_back(card);
		}
	}
}

std::vector<Card> Shuffler::provideCards(const int cardSelection[8]) {
	std::vector<Card> providedCards;
	for (int i = 0; i < 8; i++) {
		int idx = cardSelection[i] - i;
		providedCards.push_back(m_availableCards[idx]);
		m_availableCards.erase(m_availableCards.begin() + idx);
	}
	return providedCards;
}

std::vector<Card> Shuffler::provideCards() {
	std::vector<Card> providedCards;
	for (int i = 0; i < 8; i++) {
		int nCardsLeft = m_availableCards.size();
		int idx = (double) rand() * nCardsLeft / RAND_MAX;
		providedCards.push_back(m_availableCards[idx]);
		m_availableCards.erase(m_availableCards.begin() + idx);
	}
	return providedCards;
}

