/*
 * CedompException.h
 *
 *  Created on: Jul 8, 2016
 *      Author: mitthy
 */

#ifndef CEDOMPEXCEPTION_H_
#define CEDOMPEXCEPTION_H_
#include <exception>
#include <string>
namespace Cedomp
{
	namespace Exceptions
	{
		class CedompException: public std::exception
		{
		public:
			virtual ~CedompException() = default;
			void PrintSemanticError();
		protected:
			virtual std::string Error() = 0;
		};
	}
}

#endif /* CEDOMPEXCEPTION_H_ */
