/*
 * gamesession.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include "game.hpp"
#include <cassert>
#include <vector>
#include <cstring>

int countStichPoints(std::vector<Card> stich);
int lookupPoints(Schlag schlag);

GameSession::GameSession(std::vector<Card> handCards[4], bool simulation) :
		m_points { 0 }, m_currentRound(0), m_simulation(simulation) {
	for (int i = 0; i < 4; i++) {
		m_handCards[i] = handCards[i];
	}
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

