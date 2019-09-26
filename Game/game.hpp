/*
 * game.hpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <stdexcept>

enum Farbe {
	SCHELLEN, HERZ, GRAS, EICHEL
};

enum Schlag {
	SIEBEN, ACHT, NEUN, U, O, K, ZEHN, A
};

struct Card {
	Farbe farbe;
	Schlag schlag;
};

struct GameResult {
	bool isFinished;
	bool winner[4];
	int points;
};

enum GameType{
	None, Sauspiel
};

typedef std::vector<Card> Stich;

class GameSession {

public:
	GameSession(std::vector<Card> handCards[4], bool simulation);
	virtual ~GameSession();
	virtual std::vector<Card> getPossible(std::vector<Card> handCards) = 0;
	void revertCard();
	void placeCard(int player, int card);
	void placeCardSimulation(Card card);
	int getPlayerNextTurn();
	GameResult getResult();

protected:
	std::vector<Card> m_openCards;
	int m_points[4];

private:
	void eval();
	void revertStich();
	virtual int determineStichWinner(std::vector<Card> cards) = 0;
	virtual bool* determineGameWinner() = 0;
	virtual int getWinnerPoints() = 0;

	std::vector<Stich> m_history;
	std::vector<int> m_starter;
	int m_currentRound;
	std::vector<Card> m_handCards[4];
	const bool m_simulation;
};

class Herzsolo: public GameSession {

public:
	Herzsolo(std::vector<Card> handCards[4], bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	int determineStichWinner(std::vector<Card> cards);
	bool* determineGameWinner();
	int getWinnerPoints();
};

#endif /* GAME_HPP_ */
