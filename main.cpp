/*
 * main.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include "Game/randomplayer.hpp"
#include "Game/gamecontroller.hpp"

int main() {
	GameController controller;
	for (int i = 0; i < 4; i++) {
		controller.registerPlayer(new RandomPlayer());
	}
	controller.initGame();
}

