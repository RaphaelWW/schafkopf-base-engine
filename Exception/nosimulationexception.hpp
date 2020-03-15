/*
 * nosimulationexception.hpp
 *
 *  Created on: Oct 3, 2019
 *      Author: raphael
 */

#ifndef EXCEPTION_NOSIMULATIONEXCEPTION_HPP_
#define EXCEPTION_NOSIMULATIONEXCEPTION_HPP_


#include <exception>
#include <string>

using namespace std;

class NoSimulationException: public exception {
public:
	char * what() {
		return strdup("Cannot execute because this is not a simulation.");
	}
};


#endif /* EXCEPTION_NOSIMULATIONEXCEPTION_HPP_ */
