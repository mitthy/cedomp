/*
 * TypeException.h
 *
 *  Created on: Jul 7, 2016
 *      Author: mitthy
 */

#ifndef TYPEEXCEPTION_H_
#define TYPEEXCEPTION_H_
#include "Exceptions/CedompException.h"
#include "Type/Types.h"

namespace Cedomp
{
	namespace Exceptions
	{
		class TypeException: public CedompException
		{
		public:
			virtual ~TypeException() = default;
		protected:
			virtual std::string Error() = 0;
		};

		class IncompatibleTypeException: public TypeException
		{
		public:
			IncompatibleTypeException( const Type::TypeCode& type1,
					const Type::TypeCode& type2 );
		protected:
			virtual std::string Error();
		private:
			Type::TypeCode typeCode1;
			Type::TypeCode typeCode2;
		};
	}
}

#endif /* TYPEEXCEPTION_H_ */
