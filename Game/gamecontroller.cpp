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
#include "../Exception/registrationexception.hpp"

using namespace std;

GameSession* mapGameTypeToGameSession(CommonKnowledge* common, vector<Card>* handCards);

GameController::GameController() :
		m_startPlayer(0) {
}

void GameController::registerPlayer(Player* player) {
	static int nRegistered = 0;
	if (nRegistered < 4) {
		m_players[nRegistered] = player;
		nRegistered++;
	} else {
		throw RegistrationException(string("4 players are already registered."));
	}
	if (nRegistered == 4) {
		initGame();
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

	GameSession* session = mapGameTypeToGameSession(&common, m_handCards);
	int roundStartPlayer = m_startPlayer;
	for (int i = 0; i < 8; i++) {
		roundStartPlayer = playRound(&common, session, roundStartPlayer);
	}
}

int GameController::playRound(CommonKnowledge* common, GameSession* session, int startPlayer) {
	for (int i = 0; i < 4; i++) {
		int turn = (startPlayer + i) % 4;
		Card card = m_players[turn]->placeCard(session->getPossible(m_handCards[turn]));
		session->placeCard(turn, card);
	}
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

GameSession* mapGameTypeToGameSession(CommonKnowledge* common, vector<Card>* handCards) {
	if (common->spiel.type == None) {
		throw GameStartException(string("No game decision was met."));
	}
	switch (common->spiel.type) {
	case Sauspiel:
		return new SauspielSession(handCards, common, false);
	default:
		throw GameStartException(string("Game type is not known"));
	}
}

