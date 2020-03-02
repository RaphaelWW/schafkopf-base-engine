/*
 * illegalcardexception.hpp
 *
 *  Created on: Oct 6, 2019
 *      Author: raphael
 */

#ifndef EXCEPTION_ILLEGALCARDEXCEPTION_HPP_
#define EXCEPTION_ILLEGALCARDEXCEPTION_HPP_

#include <exception>
#include <string.h>

using namespace std;

class IllegalCardException: public exception {
public:
	IllegalCardException(string msg) :
			m_msg(msg) {
	}

	char * what() {
		return strdup(m_msg.c_str());
	}

private:
	string m_msg;
};

#endif /* EXCEPTION_ILLEGALCARDEXCEPTION_HPP_ */
