/*
 * main.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include <iostream>

#include "Game/randomplayer.hpp"
#include "Game/gamecontroller.hpp"

int main() {
	GameController controller;
	for (int i = 0; i < 4; i++) {
		controller.registerPlayer(new RandomPlayer());
	}
	GameResult result = controller.initGame();
	for (int i = 0; i < 4; i++) {
		if (result.winner[i]) {
			std::cout << "Player " << i << " wins with " << result.points << "." << std::endl;
		}
	}
}

