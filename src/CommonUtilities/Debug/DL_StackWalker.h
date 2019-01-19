#pragma once

#include <windows.h>
#include "StackWalker.h"

namespace DL_Debug
{
	class StackWalker : public BaseStackWalker
	{
	public:
		StackWalker();
		StackWalker(unsigned int aProcessId, HANDLE aProcess);
		virtual void OnOutput(char* aString);
	};


};