#include "TimeManager.h"
#include <Windows.h>
#include <iostream>
#include <assert.h>

namespace CommonUtilities
{
	Timer TimeManager::myMasterTimer;

	//QueryPerformanceCounter returns the number of "ticks" since the computer was rebooted.
	//QueryPerformanceFrequency returns the number of "ticks" in a second.
	TimeManager::TimeManager()
	{
		myPCFrequancy = 0.0f;

		LARGE_INTEGER li;
		if (QueryPerformanceFrequency(&li) == false)
		{
			assert(false && "QueryPerformanceFrequency failed!");
		}

		myPCFrequancy = static_cast<float>(li.QuadPart);

		QueryPerformanceCounter(&li);

		myLastTicks = li.QuadPart;
	}


	TimeManager::~TimeManager()
	{
	}


	void TimeManager::UpdateAllTimers()
	{
		LARGE_INTEGER ticksSinceReboot;

		if (QueryPerformanceCounter(&ticksSinceReboot) == false)
		{
			assert(false && "QueryPerformanceFrequency failed!");
		}

		__int64 currentTicks = ticksSinceReboot.QuadPart;
		__int64 ticksSinceLast = currentTicks - myLastTicks;
		float deltaTime = ticksSinceLast / myPCFrequancy * 1000;
		myLastTicks = currentTicks;

		myMasterTimer.Update(static_cast<float>(deltaTime));

		for (size_t i = 0; i < myTimers.size(); i++)
		{
			myTimers[i].Update(static_cast<float>(deltaTime));
		}
	}

	void TimeManager::PauseAllTimers()
	{
		for (size_t i = 0; i < myTimers.size(); i++)
		{
			myTimers[i].StopTimer();
		}
	}

	void TimeManager::StartAllTimers()
	{
		for (size_t i = 0; i < myTimers.size(); i++)
		{
			myTimers[i].StartTimer();
		}
	}

	const Timer &TimeManager::GetTimer(const unsigned int aIndex)
	{
		if (aIndex < static_cast<unsigned int>(myTimers.size()))
		{
			return myTimers[aIndex];
		}
		else
		{
			assert(false && "Index out of bounds: GetTimer");
		}
		return myTimers[0];
	}

	unsigned int TimeManager::CreateTimer()
	{
		Timer t;
		myTimers.push_back(t);
		return static_cast<unsigned int>(myTimers.size() - 1);
	}

	void TimeManager::StopATimer(const unsigned int aIndex)
	{
		if (aIndex < static_cast<unsigned int>(myTimers.size()))
		{
			myTimers[aIndex].StopTimer();
		}
		else
		{
			assert(false && "Index out of bounds: GetTimer");
		}
	}
}