/*
 * treebuilder.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: raphael
 */

#include <vector>
#include <algorithm>
#include <iostream>

#include "Game/gamesession.hpp"
#include "SimulationTree/treebuilder.hpp"

bool operator==(const Card card1, const Card card2);
void removeCardFromOptions(std::vector<Card> possibleCards[4], Card toRemove, int idxRemoved[4]);
void resetOptions(std::vector<Card> possibleCards[4], Card card, int idxCard[4]);

TreeBuilder::TreeBuilder(GameSession* game) {
	m_game = game;
}

unsigned long TreeBuilder::countCombs(std::vector<Card> cardsP0) {
	std::vector<Card> possibleCards[4];
	possibleCards[0] = cardsP0;
	for (int i = 1; i < 4; i++) {
		possibleCards[i] = std::vector<Card>();
	}

	for (int schlag = SIEBEN; schlag <= A; schlag++) {
		for (int farbe = SCHELLEN; farbe <= EICHEL; farbe++) {
			Card card;
			card.schlag = (Schlag) schlag;
			card.farbe = (Farbe) farbe;
			bool cardUsed = false;
			for (Card cardP0 : cardsP0) {
				if (card == cardP0) {
					cardUsed = true;
					break;
				}
			}
			if (!cardUsed) {
				possibleCards[1].push_back(card);
				possibleCards[2].push_back(card);
				possibleCards[3].push_back(card);
			}
		}
	}
	return countCombsRound(possibleCards, 0, 0);
}

unsigned long TreeBuilder::countCombsRound(std::vector<Card> possibleCards[4], int round, unsigned long nCombs) {

	if (round == 8) {
		if (nCombs % 1000000 == 0) {
			std::cout << nCombs << " found" << std::endl;
		}
		return nCombs + 1;
	}
	return countCombsRoundPlayer(possibleCards, round, 0, nCombs);
}

unsigned long TreeBuilder::countCombsRoundPlayer(std::vector<Card> possibleCards[4], int round, int turn,
		unsigned long nCombs) {

	if (turn == 4) {
		return countCombsRound(possibleCards, round + 1, nCombs);
	}

	int player = m_game->getPlayerNextTurn();

	std::vector<Card> possibleNow = m_game->getPossible(possibleCards[player]);

	if (possibleCards[player].size() == 0) {
		return nCombs;
	}

	for (Card card : possibleNow) {
		m_game->placeCardSimulation(card);
		int idxRemoved[] = { -1, -1, -1, -1 };
		removeCardFromOptions(possibleCards, card, idxRemoved);
		nCombs = countCombsRoundPlayer(possibleCards, round, turn + 1, nCombs);
		resetOptions(possibleCards, card, idxRemoved);
		m_game->revertCard();
	}

	return nCombs;
}

bool operator==(const Card card1, const Card card2) {
	return card1.schlag == card2.schlag && card1.farbe == card2.farbe;
}

void removeCardFromOptions(std::vector<Card> possibleCards[4], Card toRemove, int idxRemoved[4]) {
	for (int i = 0; i < 4; i++) {
		for (unsigned int cardIdx = 0; cardIdx < possibleCards[i].size(); cardIdx++) {
			if (possibleCards[i][cardIdx] == toRemove) {
				possibleCards[i].erase(possibleCards[i].begin() + cardIdx);
				idxRemoved[i] = cardIdx;
				break;
			}
		}
	}
}

void resetOptions(std::vector<Card> possibleCards[4], Card card, int idxCard[4]) {
	for (int i = 0; i < 4; i++) {
		if (idxCard[i] >= 0) {
			possibleCards[i].insert(possibleCards[i].begin() + idxCard[i], card);
		}
	}
}

