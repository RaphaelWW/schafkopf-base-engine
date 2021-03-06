/*
 * consoleplayer.hpp
 *
 *  Created on: Oct 13, 2019
 *      Author: raphael
 */

#ifndef GAME_CONSOLEPLAYER_HPP_
#define GAME_CONSOLEPLAYER_HPP_

#include "Game/game.hpp"

using namespace std;

class ConsolePlayer: public Player{
public:
	Spiel vote(GameSituation sit, vector<Spiel> possibleVotes);
	Card placeCard(vector<Card> possibleCards);

private:
	GameSituation m_sit;
	bool m_spielAnnounced;
};

#endif /* GAME_CONSOLEPLAYER_HPP_ */
