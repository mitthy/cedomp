/*
 * ExpressionException.h
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#ifndef EXPRESSIONEXCEPTION_H_
#define EXPRESSIONEXCEPTION_H_
#include "CedompException.h"
#include <string>
namespace Cedomp
{
	namespace Exceptions
	{
		class ExpressionException: public CedompException
		{
		protected:
			virtual std::string Error() = 0;
		};

		class VariableNotDeclaredIndexedException: public ExpressionException
		{
		public:
			VariableNotDeclaredIndexedException( const std::string& varName );
		protected:
			virtual std::string Error();
		private:
			std::string varName;
		};

		class VariableNotDeclaredException: public ExpressionException
		{
		public:
			VariableNotDeclaredException(const std::string& id );
		protected:
			virtual std::string Error();
		private:
			std::string varName;
		};

	}
}

#endif /* EXPRESSIONEXCEPTION_H_ */
