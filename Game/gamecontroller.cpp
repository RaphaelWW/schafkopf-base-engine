/*
 * gamecontroller.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: raphael
 */
#include <string>
#include <vector>
#include <cstring>

#include "game.hpp"
#include "gamecontroller.hpp"
#include "shuffler.hpp"
#include "gametype.hpp"

#include "../Exception/gamestartexception.hpp"
#include "../Exception/registrationexception.hpp"

using namespace std;

GameSession* mapGameTypeToGameSession(CommonKnowledge* common, vector<Card>* handCards);
vector<Spiel> getPossibleVotes(vector<Card> handCards);

GameController::GameController() :
		m_startPlayer(0), m_currentSession(NULL) {
}

void GameController::registerPlayer(Player* player) {
	static int nRegistered = 0;
	if (nRegistered < 4) {
		m_players[nRegistered] = player;
		nRegistered++;
	} else {
		throw RegistrationException(string("4 players are already registered."));
	}
}

GameResult GameController::initGame() {
	CommonKnowledge common;
	common.startPlayer = m_startPlayer;
	common.spiel.type = None;
	createGameSituations(&common);

	for (int i = 0; i < 4; i++) {
		int playerTurn = (common.startPlayer + i) % 4;
		Spiel vote = m_players[playerTurn]->vote(situations[playerTurn], getPossibleVotes(m_handCards[playerTurn]));
		if (vote.type == Sauspiel && common.spiel.type == None) {
			common.spieler = playerTurn;
			common.spiel = vote;
		}
	}

	try {
		m_currentSession = mapGameTypeToGameSession(&common, m_handCards);
	} catch (GameStartException*) {
		GameResult result;
		result.isFinished = false;
		result.points = 0;
		bool winners[] = {false,false,false,false};
		memcpy(result.winner, winners, 4);
		return result;
	}
	for (int i = 0; i < 8; i++) {
		common.startPlayer = playRound(&common, m_currentSession, common.startPlayer);
	}

	m_startPlayer = (m_startPlayer + 1) % 4;
	notifyEnd();
	return m_currentSession->getResult();
}

int GameController::playRound(CommonKnowledge* common, GameSession* session, int startPlayer) {
	for (int i = 0; i < 4; i++) {
		int turn = (startPlayer + i) % 4;
		Card card = m_players[turn]->placeCard(session->getPossible(m_handCards[turn]));
		session->placeCard(turn, card);
	}
	return session->getPlayerNextTurn();
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
		throw new GameStartException(string("No game decision was met."));
	}
	switch (common->spiel.type) {
	case Sauspiel:
		return new SauspielSession(handCards, common, false);
	default:
		throw new GameStartException(string("Game type is not known"));
	}
}

GameSession* GameController::getCurrentGameSession() {
	return m_currentSession;
}

void GameController::notifyEnd() {
	for (int i = 0; i < 4; i++) {
		m_players[i]->notifyEnd();
	}
}

vector<Spiel> getPossibleVotes(vector<Card> handCards) {
	vector<Spiel> possibles;
	for (GameTypeName name = None; name <= Sauspiel; name = (GameTypeName) ((int) name + 1)) {
		GameType* gameType = GameType::gameTypeFromName(name);
		vector<Spiel> newPossibles = gameType->getPossibleVariants(handCards);
		possibles.insert(possibles.end(), newPossibles.begin(), newPossibles.end());
	}
	return possibles;
}

