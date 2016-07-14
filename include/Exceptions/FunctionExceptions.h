/*
 * FunctionExceptions.h
 *
 *  Created on: Jul 12, 2016
 *      Author: mitthy
 */

#ifndef FUNCTIONEXCEPTIONS_H_
#define FUNCTIONEXCEPTIONS_H_
#include "CedompException.h"
#include <string>
#include "Type/Types.h"
#include <vector>
namespace Cedomp
{
	namespace Exceptions
	{
		class FunctionException: public CedompException
		{
		protected:
			virtual std::string Error() = 0;
		};

		class FunctionContextException: public FunctionException
		{
		protected:
			virtual std::string Error();
		};

		class VariableAsFunction: public FunctionException
		{
		public:
			VariableAsFunction( const std::string& id );
		protected:
			virtual std::string Error();
		private:
			std::string id;
		};

		class ReturnOutsideFunction: public FunctionException
		{
		protected:
			virtual std::string Error();
		};

		class IncompatibleReturnType: public FunctionException
		{
		public:
			IncompatibleReturnType();
		protected:
			virtual std::string Error();
		};

		class RedeclarationOfFunction: public FunctionException
		{
		public:
			RedeclarationOfFunction( const std::string& id );
		protected:
			virtual std::string Error();
		private:
			std::string id;
		};

		class WrongNumberOfArguments: public FunctionException
		{
		public:
			WrongNumberOfArguments( int expected, int actual );
		protected:
			virtual std::string Error();
		private:
			int actual;
			int expected;
		};
	}
}

#endif /* FUNCTIONEXCEPTIONS_H_ */
