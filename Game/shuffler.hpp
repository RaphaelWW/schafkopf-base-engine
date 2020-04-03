/*
 * shuffler.hpp
 *
 *  Created on: Aug 17, 2019
 *      Author: raphael
 */

#ifndef SHUFFLER_HPP_
#define SHUFFLER_HPP_

#include "Game/game.hpp"
#include <vector>

using namespace std;

class Shuffler {
public:
	Shuffler();
	vector<Card> provideCards(const int cardSelection[8]);
	vector<Card> provideCards();

private:
	vector<Card> m_availableCards;
};

#endif /* SHUFFLER_HPP_ */
