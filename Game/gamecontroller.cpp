/*
 * gamecontroller.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: raphael
 */
#include <optional>

#include "gamecontroller.hpp"

using namespace std;

int determineSpieler(GameType* votes);

GameController::GameController(int startPlayer) :
		m_game(NULL), m_startPlayer(startPlayer), m_nVotes(0), m_spieler(-1) {
}

void GameController::vote(int player, GameType choice) {
	if (player == (m_startPlayer + m_nVotes) % 4) {
		m_vote[player] = choice;
		m_nVotes++;
	}
	if (m_nVotes == 4) {
		m_spieler = determineSpieler(m_vote);
		m_game = m_vote[m_spieler];
	}
}

int determineSpieler(GameType* votes) {
	GameType winner = None;
	int spieler = -1;
	for (int i = 0; i < 4; i++) {
		if (votes[i] > winner) {
			winner = votes[i];
			spieler = i;
		}
	}
	return spieler;
}

