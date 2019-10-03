/*
 * gamesession.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>

#include "game.hpp"

int determineFarbstichWinner(std::vector<Card> cards);
bool isCardHigherFarbe(Card card1, Card card2);
int countStichPoints(std::vector<Card> stich);
int lookupPoints(Schlag schlag);

GameSession::GameSession(std::vector<Card>* handCards, bool simulation) :
		m_points { 0 }, m_currentRound(0), m_simulation(simulation) {
	m_handCards = handCards;
	m_starter.push_back(0);
}

GameSession::~GameSession() {
}

void GameSession::revertStich() {
	assert(m_simulation);
	assert(m_currentRound > 0);
	m_currentRound--;
	int winner = m_starter.back();
	m_starter.pop_back();
	m_openCards = m_history.back();
	m_points[winner] -= countStichPoints(m_openCards);
	m_history.pop_back();
	m_openCards.pop_back();
}

int GameSession::determineStichWinner(std::vector<Card> cards) {
	int winningPlayer = determineHighestTrumpf(cards);
	if (winningPlayer > -1) {
		return winningPlayer;
	}

	return determineFarbstichWinner(cards);
}

//returns number of the player with the highest Trumpf, -1 if none played Trumpf
int GameSession::determineHighestTrumpf(std::vector<Card> cards) {
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

bool isCardHigherFarbe(Card card1, Card card2) {
	return card1.farbe == card2.farbe && card1.schlag < card2.schlag;
}

std::vector<Card> GameSession::findAllTrumpf(std::vector<Card> cards) {
	std::vector<Card> trumpf;
	for(Card card : cards){
		if(isTrumpf(card)){
			trumpf.push_back(card);
		}
	}
	return trumpf;
}

std::vector<Card> GameSession::findAllInFarbe(std::vector<Card> cards, Farbe farbe) {
	std::vector<Card> cardsInFarbe;
	std::copy_if(cards.begin(), cards.end(), std::back_inserter(cardsInFarbe),
			[farbe](Card card) {return card.farbe == farbe;});
	return cardsInFarbe;
}

void GameSession::revertCard() {
	assert(m_simulation);
	if (m_openCards.empty()) {
		revertStich();
	} else {
		m_openCards.pop_back();
	}
}

void GameSession::placeCard(int player, int card) {
	assert(8 - m_currentRound == (int ) m_handCards[player].size());
	assert(!m_openCards.empty() || m_starter.back() == player);
	m_openCards.push_back(m_handCards[player][card]);
	m_handCards[player].erase(m_handCards[player].begin() + card);
	if (m_openCards.size() == 4) {
		eval();
	}
}

void GameSession::placeCardSimulation(Card card) {
	assert(m_simulation);
	m_openCards.push_back(card);
	if (m_openCards.size() == 4) {
		eval();
	}
}

void GameSession::eval() {
	assert(m_openCards.size() == 4);
	int winner = (determineStichWinner(m_openCards) + m_starter.back()) % 4;
	m_points[winner] += countStichPoints(m_openCards);
	m_currentRound++;
	m_starter.push_back(winner);
	m_history.push_back(m_openCards);
	m_openCards.clear();
}

int GameSession::getPlayerNextTurn() {
	if (m_starter.empty()) {
		return 0;
	}
	return (m_starter.back() + m_openCards.size()) % 4;
}

GameResult GameSession::getResult() {
	GameResult result;
	if (m_currentRound < 8) {
		result.isFinished = false;
		result.points = -1;
	} else {
		result.isFinished = true;
		bool* winner = determineGameWinner();
		memcpy(result.winner, winner, 4 * sizeof(bool));
		delete winner;
		result.points = getWinnerPoints();
	}
	return result;
}

int countStichPoints(Stich stich) {
	int sum = 0;
	for (Card card : stich) {
		sum += lookupPoints(card.schlag);
	}
	return sum;
}

int lookupPoints(Schlag schlag) {
	switch (schlag) {
	case A:
		return 11;
	case K:
		return 4;
	case O:
		return 3;
	case U:
		return 2;
	default:
		return 0;
	}
}

