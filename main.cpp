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
#include "Game/consoleplayer.hpp"

int main() {
	int wins[4] = { 0 };
	GameController controller;
	for (int i = 0; i < 3; i++) {
		controller.registerPlayer(new RandomPlayer());
	}
	controller.registerPlayer(new TcpPlayer("127.0.0.1", 8080, &controller, 3));
	//controller.registerPlayer(new ConsolePlayer());

	for (int i = 0; i < 100000; i++) {
		GameResult result = controller.initGame();
		std::cout << "\r" << "Games won: ";
		for (int i = 0; i < 4; i++) {
			if (result.winner[i]) {
				wins[i]++;
			}
			std::cout << wins[i] << " ";
		}
	}
}

