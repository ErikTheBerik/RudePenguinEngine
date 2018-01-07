#pragma once
#include <vector>
#include "Timer.h"
#include "Time.h"

namespace CommonUtilities
{
	class TimeManager
	{
	public:
		TimeManager();
		~TimeManager();
		void UpdateAllTimers();
		void PauseAllTimers();
		void StartAllTimers();
		void StopATimer(unsigned const int aIndex);
		const Timer &GetTimer(const unsigned int aIndex);
		unsigned int CreateTimer();
		inline static const Time & GetDeltaTime();
	private:
		static Timer myMasterTimer;
		std::vector<Timer> myTimers;
		float myPCFrequancy;
		__int64 myLastTicks;
	};

	inline const Time & TimeManager::GetDeltaTime()
	{
		return myMasterTimer.GetTimeSinceLastFrame();
	}
}
