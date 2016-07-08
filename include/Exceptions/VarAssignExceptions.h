/*
 * Exceptions.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_
#include <exception>
#include <string>

namespace Cedomp
{
	namespace Exceptions
	{

		class VarAssignException : public std::exception
		{

		};

		class FunctionAsVariable : public VarAssignException
		{
		public:
			FunctionAsVariable(const std::string& funcName);
		};

		class WrongVarNumberException : public VarAssignException
		{
		public:
			WrongVarNumberException(unsigned int, unsigned int);
		};

	}
}



#endif /* EXCEPTIONS_H_ */
