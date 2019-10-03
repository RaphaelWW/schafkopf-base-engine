/*
 * gamecontroller.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: raphael
 */
#include <string>
#include <vector>

#include "game.hpp"
#include "gamecontroller.hpp"
#include "shuffler.hpp"
#include "../Exception/gamestartexception.hpp"

using namespace std;

GameSession* mapGameTypeToGameSession(Spiel spiel, vector<Card>* handCards);

GameController::GameController() :
		m_startPlayer(0) {
}

void GameController::registerPlayer(Player* player) {
	if (m_players.size() < 4) {
		m_players.push_back(player);
	} else {

	}
}

void GameController::initGame() {
	CommonKnowledge common;
	common.startPlayer = m_startPlayer;
	common.spiel.type = None;
	createGameSituations(&common);

	for (int i = 0; i < 4; i++) {
		Spiel vote = m_players[i]->vote(situations[i]);
		if (vote.type == Sauspiel && common.spiel.type == None) {
			common.spieler = i;
			common.spiel = vote;
		}
	}

	GameSession* session = mapGameTypeToGameSession(common.spiel, m_handCards);
}

void GameController::createGameSituations(CommonKnowledge* common) {
	Shuffler shuffler;
	for (int i = 0; i < 4; i++) {
		situations[i] = GameSituation();
		m_handCards[i] = shuffler.provideCards();
		situations[i].handCards = &m_handCards[i];
		situations[i].common = common;
	}
}

GameSession* mapGameTypeToGameSession(Spiel spiel, vector<Card>* handCards) {
	if (spiel.type == None) {
		throw GameStartException(string("No game decision was met."));
	}
	switch (spiel.type) {
	case Sauspiel:
		return new SauspielSession(handCards, spiel.farbe, false);
	default:
		throw GameStartException(string("Game type is not known"));
	}
}

