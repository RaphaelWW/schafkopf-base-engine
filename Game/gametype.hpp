/*
 * gametype.hpp
 *
 *  Created on: Mar 15, 2020
 *      Author: raphael
 */

#ifndef GAME_GAMETYPE_HPP_
#define GAME_GAMETYPE_HPP_

#include "Game/game.hpp"

#include <vector>

using namespace std;

class GameType {

public:
	static GameType* gameTypeFromName(GameTypeName name);
	virtual vector<Spiel> getPossibleVariants(vector<Card> handCards) = 0;
	virtual ~GameType();
};



#endif /* GAME_GAMETYPE_HPP_ */
