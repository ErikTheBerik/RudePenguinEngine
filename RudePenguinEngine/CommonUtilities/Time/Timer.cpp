#include "Timer.h"
#include <iostream>
#include <cmath>

namespace CommonUtilities
{

	Timer::Timer()
	{
		myIsRunning = true;
		myNumberOfTimesCalled = 0;
		myLastFPS = 0.f;
	}

	Timer::~Timer()
	{
	}

	void Timer::Update(const float aDeltaTime)
	{
		if (myIsRunning == true)
		{
			myTime.AddTime(aDeltaTime);
			myLastUpdate.SetTime(aDeltaTime);
			myNumberOfTimesCalled++;
			if (myTime.GetSeconds() - floor(myTime.GetSeconds()) > 0.999f)
			{
				myLastFPS = 1 / myLastUpdate.GetSeconds();
			}
		}
	}

	void Timer::StartTimer()
	{
		myIsRunning = true;
	}

	void Timer::StopTimer()
	{
		myIsRunning = false;
	}

	const Time &Timer::GetTime() const
	{
		return myTime;
	}

	const Time &Timer::GetTimeSinceLastFrame() const
	{
		return myLastUpdate;
	}

	const float Timer::GetFPS()
	{	
		return myLastFPS;
	}

}