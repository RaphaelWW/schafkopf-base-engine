/*
 * httpplayer.hpp
 *
 *  Created on: Oct 31, 2019
 *      Author: raphael
 */

#ifndef GAME_TCPPLAYER_CPP_
#define GAME_TCPPLAYER_CPP_

#include "Game/game.hpp"
#include "Game/serialize.hpp"
#include "Exception//illegalcardexception.hpp"
#include "Game/gamecontroller.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <random>

#define CMD_SIZE 4
#define CMD_RESULT "RSLT"
#define CMD_VOTE "VOTE"
#define CMD_PLACE_CARD "PLAY"
#define RESP_VOTE_TYPE_NONE 0
#define RESP_VOTE_TYPE_SAUSPIEL 1

using namespace std;

class TcpPlayer: public Player {
public:
	Spiel vote(GameSituation sit, vector<Spiel> possibleVotes) {
		m_sit = sit;
		send(m_sockfd, CMD_VOTE, CMD_SIZE, 0);
		sendGameSituation();

		char buffer[SPIEL_SIZE];
		read(m_sockfd, buffer, SPIEL_SIZE);
		//return deserializeSpiel(buffer);
		return possibleVotes[rand() % possibleVotes.size()];
	}

	Card placeCard(vector<Card> possibleCards) {
		if (m_sit.common->last.size()) {
			sendResultsLastStich(possibleCards);
		}
		send(m_sockfd, CMD_PLACE_CARD, CMD_SIZE, 0);
		sendGameSituation();
		sendHandCards(possibleCards);

		char buffer[1];
		read(m_sockfd, buffer, 1);

		if ((uint8_t) *buffer > possibleCards.size()) {
			throw IllegalCardException(string("Card index chosen by TCP player out of bounds"));
		}

		return possibleCards[(uint8_t) buffer[0]];
	}

	void sendResultsLastStich(vector<Card> possibleCards) {
		uint8_t pointsLastStich = m_gameController->getCurrentGameSession()->getTeamPointsLastStich(m_player);
		send(m_sockfd, CMD_RESULT, CMD_SIZE, 0);
		send(m_sockfd, &pointsLastStich, 1, 0);
		sendGameSituation();
		sendHandCards(possibleCards);

		char buffer[1] = { 0 };
		if (!read(m_sockfd, buffer, 1)) {
			throw new runtime_error("No acknowledgement for points msg received.");
		}
	}

	void notifyEnd() {
		sendResultsLastStich(vector<Card>());
	}

	TcpPlayer(const char* ip, unsigned short int port, GameController* gameController, int player) :
			m_gameController(gameController), m_player(player) {

		m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in serv_addr;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(port);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr);
		connect(m_sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	}

private:
	void sendGameSituation() {
		serializeGameSituation(m_sit, m_gameSituationBuffer);
		send(m_sockfd, m_gameSituationBuffer, GAME_SITUATION_SIZE, 0);

	}

	void sendHandCards(vector<Card> cards){
		serializeHandCards(cards, m_possibleCardsBuffer);
		send(m_sockfd, m_possibleCardsBuffer, HAND_CARDS_SIZE, 0);
	}

	GameSituation m_sit;
	int m_sockfd;
	uint8_t m_gameSituationBuffer[GAME_SITUATION_SIZE];
	uint8_t m_possibleCardsBuffer[HAND_CARDS_SIZE];
	GameController* m_gameController;
	int m_player;

}
;

#endif /* GAME_TCPPLAYER_CPP_ */
