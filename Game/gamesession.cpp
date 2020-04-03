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
#include <stdexcept>

#include "Game/gamesession.hpp"

#include "Exception/nosimulationexception.hpp"
#include "Exception/illegalcardexception.hpp"

int determineFarbstichWinner(std::vector<Card> cards);
bool isCardHigherFarbe(Card card1, Card card2);
int lookupPoints(Schlag schlag);
void checkSimulation(bool simulation);
void updateCommon(CommonKnowledge* common, std::vector<Card> last, std::vector<Card> current);

GameSession::GameSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation) :
		m_points { 0 }, m_currentRound(0), m_simulation(simulation), m_handCards(handCards), m_common(common) {
	m_starter.push_back(common->startPlayer);
}

GameSession::~GameSession() {
}

void GameSession::revertStich() {
	checkSimulation(m_simulation);
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
	for (Card card : cards) {
		if (isTrumpf(card)) {
			trumpf.push_back(card);
		}
	}
	return trumpf;
}

std::vector<Card> GameSession::findAllInFarbe(std::vector<Card> cards, Farbe farbe) {
	std::vector<Card> cardsInFarbe;
	std::copy_if(cards.begin(), cards.end(), std::back_inserter(cardsInFarbe),
			[farbe, this](Card card) {return card.farbe == farbe && !this->isTrumpf(card);});
	return cardsInFarbe;
}

int GameSession::getSpieler() {
	return m_common->spieler;
}

std::vector<Card> GameSession::getOpenCards() {
	return m_openCards;
}

void GameSession::revertCard() {
	checkSimulation(m_simulation);
	if (m_openCards.empty()) {
		revertStich();
	} else {
		m_openCards.pop_back();
	}
}

void GameSession::placeCard(int player, Card card) {
	assert(8 - m_currentRound == (int ) m_handCards[player].size());
	assert(!m_openCards.empty() || m_starter.back() == player);

	vector<Card>::iterator placeInHand = find_if(m_handCards[player].begin(), m_handCards[player].end(),
			[card](Card cardInHand) {return card.schlag==cardInHand.schlag && card.farbe==cardInHand.farbe;});
	if (placeInHand == m_handCards[player].end()) {
		throw IllegalCardException(string("Player does not have played card."));
	}

	m_openCards.push_back(card);
	m_handCards[player].erase(placeInHand);

	if (m_openCards.size() == 4) {
		eval();
	}

	if (m_history.size() == 0) {
		updateCommon(m_common, std::vector<Card>(), m_openCards);
	} else {
		updateCommon(m_common, m_history.back(), m_openCards);
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

int GameSession::countStichPoints(Stich stich) {
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
	case ZEHN:
		return 10;
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

void checkSimulation(bool simulation) {
	if (!simulation) {
		throw NoSimulationException();
	}
}

int GameSession::getWinnerPoints() {
	bool* winner = determineGameWinner();
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		if (winner[i]) {
			sum += m_points[i];
		}
	}
	delete winner;
	return sum;
}

void updateCommon(CommonKnowledge* common, std::vector<Card> last, std::vector<Card> current) {
	common->current = current;
	common->last = last;
}

int GameSession::getTeamPointsLastStich(int player){
	if(!m_history.size()){
		throw runtime_error("Trying to get points of last Stich in first round");
	}
	if(isSameTeam(m_starter.back(), player)){
		return countStichPoints(m_history.back());
	}
	return 0;
}

