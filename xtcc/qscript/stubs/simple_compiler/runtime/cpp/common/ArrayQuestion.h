#ifndef QSCRIPT_ARRAY_QUESTION
#define QSCRIPT_ARRAY_QUESTION

#include <sys/types.h>
#include <vector>
#include "question.h"

class ArrayQuestion
{
	public:
		std::vector<AbstractRuntimeQuestion*> questionList;
		std::vector<int32_t> arrayBounds;
		ArrayQuestion()
			: questionList(), arrayBounds()
		{ }
		ArrayQuestion(vector<int32_t>& l_arrayBounds): arrayBounds(l_arrayBounds)
		{
			int32_t bounds = 1;
			for(int32_t i = 0; i<arrayBounds.size(); ++i)
			{
				bounds*=arrayBounds[i];
			}
			questionList.reserve(bounds);
		}
		void SetArrayBounds(vector<int32_t>& l_arrayBounds)
		{
			arrayBounds = l_arrayBounds;
			int32_t bounds = 1;
			for(int32_t i = 0; i<arrayBounds.size(); ++i)
			{
				bounds*=arrayBounds[i];
			}
			questionList.reserve(bounds);
		}
};

#endif /* QSCRIPT_ARRAY_QUESTION */
