/*
 * nogamedecision.hpp
 *
 *  Created on: Sep 30, 2019
 *      Author: raphael
 */

#ifndef EXCEPTION_GAMESTARTEXCEPTION_HPP_
#define EXCEPTION_GAMESTARTEXCEPTION_HPP_

#include <exception>
#include <string.h>

using namespace std;

class GameStartException: public exception {
public:
	GameStartException(string msg) :
			m_msg(msg) {
	}

	char * what() {
		return strdup(m_msg.c_str());
	}

private:
	string m_msg;
};

#endif /* EXCEPTION_GAMESTARTEXCEPTION_HPP_ */
