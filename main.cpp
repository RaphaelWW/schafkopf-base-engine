/*
 * main.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: raphael
 */

#include <iostream>

#include "Game/randomplayer.hpp"
#include "Game/gamecontroller.hpp"
#include "Game/tcpplayer.cpp"

int main() {
	int wins[4] = { 0 };
	GameController controller;
	controller.registerPlayer(new TcpPlayer("127.0.0.1", 8080, &controller, 4));
	for (int i = 0; i < 3; i++) {
		controller.registerPlayer(new RandomPlayer());
	}
	for (int i = 0; i < 1000; i++) {
		GameResult result = controller.initGame();
		for (int i = 0; i < 4; i++) {
			if (result.winner[i]) {
				wins[i]++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		std::cout << "Player " << i << " has " << wins[i] << " wins." << std::endl;
	}
}

