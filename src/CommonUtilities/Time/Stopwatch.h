#pragma once
#include "Time.h"

namespace CommonUtilities
{
	class Stopwatch
	{
	public:
		Stopwatch();
		~Stopwatch();

		void Restart();

		Time GetElapsedTime() const;

	private:
		__int64 myStartTime;
		float myFrequency;
	};
}

