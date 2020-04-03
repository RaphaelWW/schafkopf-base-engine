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

#include "gamesession.hpp"

using namespace std;

class GameController {
public:
	GameController();
	void registerPlayer(Player* player);
	GameResult initGame();
	GameSession* getCurrentGameSession();

private:
	void createGameSituations(CommonKnowledge* common);
	int playRound(CommonKnowledge* common, GameSession* session, int startPlayer);
	void notifyEnd();

	Player* m_players[4];
	vector<Card> m_handCards[4];
	GameSituation situations[4];
	int m_startPlayer;
	GameSession* m_currentSession;
};

#endif /* GAME_GAMECONTROLLER_HPP_ */
