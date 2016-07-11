/*
 * Operations.h
 *
 *  Created on: Jul 10, 2016
 *      Author: mitthy
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_
#include "Type/Types.h"
#include <string>
#include <map>
namespace Cedomp
{

	namespace Type
	{
		class Operation
		{
		public:

			static Operation getInstance();

			void registerBinaryOperation( TypeCode type1,
					const std::string& operation, TypeCode type2,
					TypeCode returnType );

			void registerUnaryOperation( TypeCode type, const std::string& operation,
					TypeCode ret );

			bool getReturnBinaryType( TypeCode type1,
					const std::string& operation, TypeCode type2,
					TypeCode& ret );

			bool getReturnUnaryType( TypeCode type, const std::string& operation,
					TypeCode& ret );


		private:
			std::map<TypeCode, std::map<std::string, std::map<TypeCode, TypeCode>>> binaryOpMap;
			std::map<TypeCode, std::map<std::string, TypeCode>> unaryOpMap;
			void initializeBinaryOpMap();
			void initializeUnaryOpMap();
			Operation();
		};
	}

}

#endif /* OPERATIONS_H_ */
