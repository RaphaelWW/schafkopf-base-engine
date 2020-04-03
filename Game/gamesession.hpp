/*
 * gamesession.hpp
 *
 *  Created on: Apr 3, 2020
 *      Author: raphael
 */

#ifndef GAME_GAMESESSION_HPP_
#define GAME_GAMESESSION_HPP_

#include <vector>

#include "game.hpp"

using namespace std;

class GameSession {

public:
	GameSession(vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	virtual ~GameSession();
	virtual vector<Card> getPossible(vector<Card> handCards) = 0;
	void revertCard();
	void placeCard(int player, Card card);
	void placeCardSimulation(Card card);
	int getPlayerNextTurn();
	GameResult getResult();
	int getTeamPointsLastStich(int player);
	static int countStichPoints(Stich stich);

protected:
	std::vector<Card> findAllTrumpf(vector<Card> cards);
	std::vector<Card> findAllInFarbe(vector<Card> cards, Farbe farbe);
	int getSpieler();
	vector<Card> getOpenCards();
	int m_points[4];

private:
	void eval();
	void revertStich();
	int determineStichWinner(vector<Card> cards);
	int determineHighestTrumpf(vector<Card> cards);
	virtual bool isTrumpf(Card card) = 0;
	virtual bool isCardHigherTrumpf(Card card1, Card card2) = 0;
	virtual bool* determineGameWinner() = 0;
	int getWinnerPoints();
	virtual bool isSameTeam(int player1, int player2) = 0;

	std::vector<Card> m_openCards;
	std::vector<Stich> m_history;
	std::vector<int> m_starter;
	int m_currentRound;
	const bool m_simulation;
	std::vector<Card>* m_handCards;
	CommonKnowledge* m_common;
};

class HerzsoloSession: public GameSession {

public:
	HerzsoloSession(vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	vector<Card> getPossible(vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
	bool isSameTeam(int player1, int player2);
};

class SauspielSession: public GameSession {

public:
	SauspielSession(vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	vector<Card> getPossible(vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
	bool isSameTeam(int player1, int player2);
	bool isPossible(vector<Card> handCards);

	Farbe m_farbe;
	int m_mitspieler;
};




#endif /* GAME_GAMESESSION_HPP_ */
