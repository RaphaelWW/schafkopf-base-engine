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
