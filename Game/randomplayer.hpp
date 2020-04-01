/*
 * humanplayer.hpp
 *
 *  Created on: Oct 8, 2019
 *      Author: raphael
 */

#ifndef GAME_RANDOMPLAYER_HPP_
#define GAME_RANDOMPLAYER_HPP_

#include <random>

#include "game.hpp"

using namespace std;

class RandomPlayer: public Player{
public:
	Spiel vote(GameSituation sit, vector<Spiel> possibleVotes);
	Card placeCard(vector<Card> possibleCards);
};


#endif /* GAME_RANDOMPLAYER_HPP_ */
