/*
 * serialize.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: raphael
 */

#ifndef GAME_SERIALIZE_CPP_
#define GAME_SERIALIZE_CPP_

#include "serialize.hpp"

#include <cstring>

void serializeCard(Card card, uint8_t* byte_repr);
void serializeSpiel(Spiel spiel, uint8_t* byte_repr);
void serializeOpenCards(vector<Card> cards, uint8_t* byte_repr);
void serializeCardVector(vector<Card> cards, uint8_t* byte_repr, int maxNumCards);
void serializeCommonKnowledge(CommonKnowledge common, uint8_t* byte_repr);

void serializeGameSituation(GameSituation sit, uint8_t* byte_repr) {
	serializeHandCards(*sit.handCards, byte_repr);
	serializeCommonKnowledge(*sit.common, byte_repr + HAND_CARDS_SIZE);
}

void serializeHandCards(vector<Card> cards, uint8_t* byte_repr) {
	serializeCardVector(cards, byte_repr, HAND_CARDS_SIZE);
}

void serializeOpenCards(vector<Card> cards, uint8_t* byte_repr) {
	serializeCardVector(cards, byte_repr, OPEN_CARDS_SIZE);
}

void serializeCardVector(vector<Card> cards, uint8_t* byte_repr, int maxNumCards) {
	int nCards = cards.size();
	for (int i = 0; i < nCards; i++) {
		serializeCard(cards[i], byte_repr + i * CARD_SIZE);
	}
	memset(byte_repr + CARD_SIZE * nCards, 0xff, maxNumCards - nCards * CARD_SIZE);
}

void serializeCard(Card card, uint8_t* byte_repr) {
	byte_repr[0] = (uint8_t) card.farbe;
	byte_repr[1] = (uint8_t) card.schlag;
}

void serializeCommonKnowledge(CommonKnowledge common, uint8_t* byte_repr) {
	serializeOpenCards(common.last, byte_repr);
	int next_idx = OPEN_CARDS_SIZE;
	serializeOpenCards(common.current, byte_repr + next_idx);
	next_idx += OPEN_CARDS_SIZE;
	byte_repr[next_idx] = (uint8_t) common.startPlayer;
	next_idx += 1;
	byte_repr[next_idx] = (uint8_t) common.spieler;
	next_idx += 1;
	serializeSpiel(common.spiel, byte_repr + next_idx);
}

void serializeSpiel(Spiel spiel, uint8_t* byte_repr) {
	byte_repr[0] = (uint8_t) spiel.type;
	byte_repr[1] = (uint8_t) spiel.farbe;
}

Spiel deserializeSpiel(char* msg) {
	Spiel spiel;
	spiel.type = (GameTypeName) (uint8_t) msg[0];
	spiel.farbe = (Farbe) (uint8_t) msg[1];
	return spiel;
}

#endif

