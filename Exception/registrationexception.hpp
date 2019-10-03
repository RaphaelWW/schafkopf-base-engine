/*
 * registrationexception.hpp
 *
 *  Created on: Oct 3, 2019
 *      Author: raphael
 */

#ifndef EXCEPTION_REGISTRATIONEXCEPTION_HPP_
#define EXCEPTION_REGISTRATIONEXCEPTION_HPP_


#include <exception>
#include <string.h>

using namespace std;

class RegistrationException: public exception {
public:
	RegistrationException(string msg) :
			m_msg(msg) {
	}

	char * what() {
		return strdup(m_msg.c_str());
	}

private:
	string m_msg;
};


#endif /* EXCEPTION_REGISTRATIONEXCEPTION_HPP_ */
