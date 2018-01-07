#pragma once
#include "Time.h"

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void StartTimer();
		void StopTimer();
		const Time &GetTime() const;
		void Update(const float aDeltaTime);
		const Time &GetTimeSinceLastFrame() const;
		const float GetFPS();
	private:
		bool myIsRunning;
		Time myTime;
		Time myLastUpdate;
		unsigned int myNumberOfTimesCalled;
		float myLastFPS;
	};

}