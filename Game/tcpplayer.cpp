/*
 * httpplayer.hpp
 *
 *  Created on: Oct 31, 2019
 *      Author: raphael
 */

#ifndef GAME_TCPPLAYER_CPP_
#define GAME_TCPPLAYER_CPP_

#include "game.hpp"
#include "serialize.hpp"
#include "../Exception/illegalcardexception.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define CMD_SIZE 4
#define CMD_VOTE "VOTE"
#define CMD_PLACE_CARD "PLAY"
#define RESP_VOTE_TYPE_NONE 0
#define RESP_VOTE_TYPE_SAUSPIEL 1

using namespace std;

class TcpPlayer: public Player {
public:
	Spiel vote(GameSituation sit) {
		m_sit = sit;
		send(m_sockfd, CMD_VOTE, CMD_SIZE, 0);
		serializeGameSituation(m_sit, m_gameSituationBuffer);
		send(m_sockfd, m_gameSituationBuffer, GAME_SITUATION_SIZE, 0);

		char buffer[SPIEL_SIZE];
		read(m_sockfd, buffer, SPIEL_SIZE);
		return deserializeSpiel(buffer);
	}

	Card placeCard(vector<Card> possibleCards) {
		send(m_sockfd, CMD_PLACE_CARD, CMD_SIZE, 0);
		serializeGameSituation(m_sit, m_gameSituationBuffer);
		send(m_sockfd, m_gameSituationBuffer, GAME_SITUATION_SIZE, 0);

		char buffer[1];
		read(m_sockfd, buffer, 1);

		if((uint8_t) buffer > possibleCards.size()){
			throw IllegalCardException(string("Card index chosen by TCP player out of bounds"));
		}

		return possibleCards[(uint8_t) buffer[0]];
	}

	TcpPlayer(const char* ip, unsigned short int port) {
		m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in serv_addr;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(port);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr);
		connect(m_sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	}

private:
	GameSituation m_sit;
	int m_sockfd;
	uint8_t m_gameSituationBuffer[GAME_SITUATION_SIZE];

}
;

#endif /* GAME_TCPPLAYER_CPP_ */
