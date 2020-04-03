/*
 * treebuilder.hpp
 *
 *  Created on: Aug 15, 2019
 *      Author: raphael
 */

#ifndef TREEBUILDER_HPP_
#define TREEBUILDER_HPP_

#include <vector>

#include "../Game/gamesession.hpp"

class TreeBuilder {
public:
	TreeBuilder(GameSession* game);
	unsigned long countCombs(std::vector<Card> cardsP0);

private:
	unsigned long countCombsRound(std::vector<Card> possibleCards[4], int round,
			unsigned long nCombs);
	unsigned long countCombsRoundPlayer(std::vector<Card> possibleCards[4], int round,
			int turn, unsigned long nCombs);

	GameSession* m_game;
};

#endif /* TREEBUILDER_HPP_ */
