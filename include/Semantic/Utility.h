/*
 * Utility.h
 *
 *  Created on: Jul 11, 2016
 *      Author: mitthy
 */

#ifndef UTILITY_H_
#define UTILITY_H_
#include <vector>
namespace Cedomp
{
	namespace Semantic
	{

		enum Context
		{
			PARSEARG, GLOBAL, IF, WHILE, DECLFUN, FUNCTION
		};

		class ContextHolder
		{
		public:
			static ContextHolder& get();
			ContextHolder(const ContextHolder& rhs) = delete;
			ContextHolder& operator=(const ContextHolder& rhs) = delete;
			Context getContext();
			void setContext(Context context);
			void restoreContext();
			bool contains(Context context);
		private:
			ContextHolder();
			std::vector<Context> context;
		};

		void CreateScope();

		void DestroyScope();

		void ChangeContext(Context context);

		Context getContext();

		void RestoreContext();

		bool ContainsContext(Context contex);

	}
}



#endif /* UTILITY_H_ */
