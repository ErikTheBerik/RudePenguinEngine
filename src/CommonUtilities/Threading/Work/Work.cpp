#include "Work.h"
#include "..\..\Debug\DL_Debug.h"

namespace CommonUtilities
{
	Work::Work(std::function<void()> aFunction)
	{
		myFunction = aFunction;
	}

	Work::Work()
	{
		myFunction = nullptr;
	}

	Work::~Work()
	{
	}

	void Work::DoWork()
	{
		if (myFunction)
		{
			myFunction();
		}
	}
}