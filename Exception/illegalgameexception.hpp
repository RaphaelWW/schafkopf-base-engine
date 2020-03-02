/*
 * illegalgameexception.hpp
 *
 *  Created on: Oct 3, 2019
 *      Author: raphael
 */

#ifndef EXCEPTION_ILLEGALGAMEEXCEPTION_HPP_
#define EXCEPTION_ILLEGALGAMEEXCEPTION_HPP_

#include <exception>
#include <string.h>

using namespace std;

class IllegalGameException: public exception {
public:
	IllegalGameException(string msg) :
			m_msg(msg) {
	}

	char * what() {
		return strdup(m_msg.c_str());
	}

private:
	string m_msg;
};

#endif /* EXCEPTION_ILLEGALGAMEEXCEPTION_HPP_ */
