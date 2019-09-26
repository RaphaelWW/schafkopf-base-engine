/*
 * shuffler.hpp
 *
 *  Created on: Aug 17, 2019
 *      Author: raphael
 */

#ifndef SHUFFLER_HPP_
#define SHUFFLER_HPP_

#include "game.hpp"
#include <vector>

class Shuffler {
public:
	Shuffler();
	std::vector<Card> provideCards(const int cardSelection[8]);
	std::vector<Card> provideCards();

private:
	std::vector<Card> m_availableCards;
};

#endif /* SHUFFLER_HPP_ */
