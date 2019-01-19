#include "Stopwatch.h"
#include <Windows.h>

namespace CommonUtilities
{
	Stopwatch::Stopwatch()
	{
		LARGE_INTEGER freq, pc;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&pc);

		myFrequency = static_cast<float>(freq.QuadPart);
		myStartTime = pc.QuadPart;
	}

	Stopwatch::~Stopwatch()
	{
	}

	CommonUtilities::Time Stopwatch::GetElapsedTime() const
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		CommonUtilities::Time returnTime;
		returnTime.SetTime(static_cast<float>(pc.QuadPart - myStartTime) / myFrequency * 1000);

		return returnTime;
	}

	void Stopwatch::Restart()
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		myStartTime = pc.QuadPart;
	}
}