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

typedef std::vector<Card> Stich;

class GameSession {

public:
	GameSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	virtual ~GameSession();
	virtual std::vector<Card> getPossible(std::vector<Card> handCards) = 0;
	void revertCard();
	void placeCard(int player, Card card);
	void placeCardSimulation(Card card);
	int getPlayerNextTurn();
	GameResult getResult();

protected:
	std::vector<Card> findAllTrumpf(std::vector<Card> cards);
	std::vector<Card> findAllInFarbe(std::vector<Card> cards, Farbe farbe);
	int getSpieler();
	int* getPoints();
	std::vector<Card> getOpenCards();


private:
	void eval();
	void revertStich();
	int determineStichWinner(std::vector<Card> cards);
	int determineHighestTrumpf(std::vector<Card> cards);
	virtual bool isTrumpf(Card card) = 0;
	virtual bool isCardHigherTrumpf(Card card1, Card card2) = 0;
	virtual bool* determineGameWinner() = 0;
	int getWinnerPoints();

	std::vector<Card> m_openCards;
	int m_points[4];
	std::vector<Stich> m_history;
	std::vector<int> m_starter;
	int m_currentRound;
	const bool m_simulation;
	std::vector<Card>* m_handCards;
	CommonKnowledge* m_common;
};

class HerzsoloSession: public GameSession {

public:
	HerzsoloSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
};

class SauspielSession: public GameSession {

public:
	SauspielSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();

	Farbe m_farbe;
	int m_mitspieler;
};

class Player {
public:
	virtual ~Player();
	virtual Spiel vote(GameSituation sit) = 0;
	virtual Card placeCard(std::vector<Card> possibleCards) = 0;
};

#endif /* GAME_HPP_ */
