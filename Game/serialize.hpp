/*
 * serialize.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: raphael
 */

#ifndef GAME_SERIALIZE_HPP_
#define GAME_SERIALIZE_HPP_

#include <string>
#include <vector>

#include "game.hpp"

using namespace std;

#define CARD_SIZE 2
#define HAND_CARDS_SIZE 8*CARD_SIZE
#define OPEN_CARDS_SIZE 4*CARD_SIZE
#define SPIEL_SIZE 2
#define COMMON_KNOWLEDGE_SIZE 2*OPEN_CARDS_SIZE + 2 + SPIEL_SIZE
#define GAME_SITUATION_SIZE HAND_CARDS_SIZE + COMMON_KNOWLEDGE_SIZE

void serializeGameSituation(GameSituation sit, uint8_t* byte_repr);
Spiel deserializeSpiel(char* msg);
void serializeHandCards(vector<Card> cards, uint8_t* byte_repr);

#endif


