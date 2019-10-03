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
	GameController();
	void registerPlayer(Player* player);
	void initGame();

private:
	void createGameSituations(CommonKnowledge* common);

	vector<Player*> m_players;
	vector<Card> m_handCards[4];
	GameSituation situations[4];
	int m_startPlayer;
};

#endif /* GAME_GAMECONTROLLER_HPP_ */
