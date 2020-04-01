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

enum GameTypeName {
	None, Sauspiel
};

struct Spiel {
	GameTypeName type;
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
	int getTeamPointsLastStich(int player);
	static int countStichPoints(Stich stich);

protected:
	std::vector<Card> findAllTrumpf(std::vector<Card> cards);
	std::vector<Card> findAllInFarbe(std::vector<Card> cards, Farbe farbe);
	int getSpieler();
	std::vector<Card> getOpenCards();
	int m_points[4];

private:
	void eval();
	void revertStich();
	int determineStichWinner(std::vector<Card> cards);
	int determineHighestTrumpf(std::vector<Card> cards);
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
	HerzsoloSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
	bool isSameTeam(int player1, int player2);
};

class SauspielSession: public GameSession {

public:
	SauspielSession(std::vector<Card>* handCards, CommonKnowledge* common, bool simulation);
	std::vector<Card> getPossible(std::vector<Card> handCards);

private:
	bool isTrumpf(Card card);
	bool isCardHigherTrumpf(Card card1, Card card2);
	bool* determineGameWinner();
	bool isSameTeam(int player1, int player2);
	bool isPossible(std::vector<Card> handCards);

	Farbe m_farbe;
	int m_mitspieler;
};

class Player {
public:
	virtual ~Player() {
	}
	;
	virtual Spiel vote(GameSituation sit, std::vector<Spiel> possibleVotes) = 0;
	virtual Card placeCard(std::vector<Card> possibleCards) = 0;
	virtual void notifyEnd() {
	}
};

#endif /* GAME_HPP_ */
