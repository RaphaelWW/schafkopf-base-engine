/*
 * helper.cpp
 *
 *  Created on: Mar 15, 2020
 *      Author: raphael
 */
#ifndef HELPER_HPP_
#define HELPER_HPP_

#include "Game/game.hpp"

#include <vector>
#include <algorithm>

using namespace std;

namespace helper {
bool containsCard(vector<Card> handCards, Card card) {
	Schlag schlag = card.schlag;
	Farbe farbe = card.farbe;
	return find_if(handCards.begin(), handCards.end(),
			[schlag,farbe](Card card) {return card.schlag == schlag && card.farbe == farbe;}) != handCards.end();
}

bool containsFarbe(vector<Card> handCards, Farbe farbe) {
	return find_if(handCards.begin(), handCards.end(), [farbe](Card card) {return card.farbe==farbe;})
			!= handCards.end();
}

bool containsFarbeNotOU(vector<Card> handCards, Farbe farbe) {
	return find_if(handCards.begin(), handCards.end(),
			[farbe](Card card) {return card.farbe==farbe && card.schlag!=O && card.schlag!=U;}) != handCards.end();
}
}

#endif

