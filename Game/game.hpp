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

enum GameType {
	None, Sauspiel
};

typedef std::vector<Card> Stich;

class GameSession {

public:
	GameSession(std::vector<Card>* handCards, bool simulation);
	virtual ~GameSession();
	virtual std::vector<Card> getPossible(std::vector<Card> handCards) = 0;
	void revertCard();
	void placeCard(int player, int card);
	void placeCardSimulation(Card card);
	int getPlayerNextTurn();
	GameResult getResult();

protected:
	std::vector<Card> findAllTrumpf(std::vector<Card> cards);
	std::vector<Card> findAllInFarbe(std::vector<Card> cards, Farbe farbe);

	std::vector<Card> m_openCards;
	int m_points[4];

private:
	void eval();
	void revertStich();
	int determineStichWinner(std::vector<Card> cards);
	int determineHighestTrumpf(std::vector<Card> cards);
	virtual bool isTrumpf(Card card) = 0;
	virtual bool isCardHigherTrumpf(Card card1, Card card2) = 0;
	virtual bool* determineGameWinner() = 0;
	virtual int getWinnerPoints() = 0;

	std::vector<Stich> m_history;
	std::vector<int> m_starter;
	int m_currentRound;
	std::vector<Card>* m_handCards;
	const bool m_simulation;
};

class HerzsoloSession: public GameSession {

public:
	HerzsoloSession(std::vector<Card>* handCards, bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
	int getWinnerPoints();
};

class SauspielSession: public GameSession {

public:
	SauspielSession(std::vector<Card>* handCards, Farbe farbe, bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
	int getWinnerPoints();

	Farbe m_farbe;
};

struct Spiel {
	GameType type;
	Farbe farbe;
};

struct CommonKnowledge {
	std::vector<Card> last;
	std::vector<Card> current;
	int startPlayer;
	int spieler;
	Spiel spiel;
};

struct GameSituation {
	std::vector<Card>* handCards;
	CommonKnowledge* common;
};

class Player {
public:
	virtual Spiel vote(GameSituation sit) = 0;
	virtual void placeCard(GameSituation sit) = 0;
};

#endif /* GAME_HPP_ */
