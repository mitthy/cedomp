/*
 * Exceptions.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_
#include <string>
#include "CedompException.h"
namespace Cedomp
{
	namespace Exceptions
	{

		class VarAssignException: public CedompException
		{
		public:
			virtual ~VarAssignException() = default;
		protected:
			virtual std::string Error() = 0;
		};

		class FunctionAsVariable: public VarAssignException
		{
		public:
			FunctionAsVariable( const std::string& funcName );
		protected:
			virtual std::string Error();
		private:
			std::string varName;
		};

		class WrongVarNumberException: public VarAssignException
		{
		public:
			WrongVarNumberException( unsigned int, unsigned int );
		protected:
			virtual std::string Error();
		private:
			unsigned int varAmount;
			unsigned int exprAmount;
		};

		class IndexNotSupportedException: public VarAssignException
		{
		public:
			IndexNotSupportedException( const std::string& varName );
		protected:
			virtual std::string Error();
		private:
			std::string varName;
		};

	}
}

#endif /* EXCEPTIONS_H_ */
