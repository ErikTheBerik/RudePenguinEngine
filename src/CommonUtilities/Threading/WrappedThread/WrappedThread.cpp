#include "WrappedThread.h"
#include "../ThreadHelper.h"
#include <thread>
#include <functional>
#include "../../Debug/DL_Debug.h"

namespace CommonUtilities
{
	WrappedThread::WrappedThread()
	{
		myFunction = nullptr;
		myPaused = false;
	}


	WrappedThread::~WrappedThread()
	{
		if (myThread != nullptr)
		{
			Stop();
		}
	}

	void WrappedThread::StartFunction(const std::function<void()> &aFunction, bool aRunContinuously, const std::string &aName)
	{
		if (myThread != nullptr)
		{
			Stop();
		}
		myFunction = std::make_shared<std::function<void()>>( std::function<void()>(aFunction));
		myRunFunction = aRunContinuously;
		myName = aName;
		myThread = std::make_unique<std::thread> (std::thread(&WrappedThread::RunFunction, this));
	}

	void WrappedThread::Stop()
	{
		myRunFunction = false;
		if (myThread != nullptr)
		{
			myThread->join();
			myThread = nullptr;
		}
	}

	bool WrappedThread::IsRunning() const
	{
		return myFunction != nullptr;
	}

	bool WrappedThread::ShouldRun() const
	{
		return myRunFunction;
	}

	void WrappedThread::Pause()
	{
		myPaused = true;
	}

	void WrappedThread::Unpause()
	{
		myPaused = false;
	}

	void WrappedThread::RunFunction()
	{
		ThreadHelper::SetThreadName(myName.c_str()); 
		do
		{
			try
			{
				if (*myFunction)
				{
					(*myFunction)();
				}
			}
			catch (...)
			{
				DL_PRINT_CONSOLE("BAD FUNCTION CALL", CONSOLE_TEXT_COLOR_RED);
			}
			while (myPaused)
				;
		} while (myRunFunction && myFunction);

		myFunction = nullptr;
	}
}