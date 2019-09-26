/*
 * gamecontroller.hpp
 *
 *  Created on: Sep 11, 2019
 *      Author: raphael
 */

#ifndef GAME_GAMECONTROLLER_HPP_
#define GAME_GAMECONTROLLER_HPP_

#include <vector>
#include <optional>

#include "game.hpp"

using namespace std;

class GameController {
public:
	GameController(int startPlayer);
	void vote(int player, GameType plays);

private:
	GameType m_vote[4];
	GameType m_game;
	int m_startPlayer, m_nVotes, m_spieler;
};

#endif /* GAME_GAMECONTROLLER_HPP_ */
