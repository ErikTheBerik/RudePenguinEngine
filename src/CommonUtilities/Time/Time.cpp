#include "Time.h"
#include <iostream>
#include <assert.h>



namespace CommonUtilities
{
	float Time::Modifier = 1.f;

	Time::Time()
	{
		myElapsedTimeInMiliseconds = 0;
	}


	Time::~Time()
	{
	}

	void Time::AddTime(float aDeltaTime)
	{
		if (aDeltaTime >= 0)
		{
			myElapsedTimeInMiliseconds += aDeltaTime;
		}
		else
		{
			assert(false && "AddTime error");
		}
	}

	void Time::SetTime(float aTime)
	{
		if (aTime >= 0)
		{
			myElapsedTimeInMiliseconds = aTime;
		}
		else
		{
			assert(false && "SetTime error");
		}
	}

	float Time::GetHours()const
	{
		return myElapsedTimeInMiliseconds / 1000 / 60 / 60 * Modifier;
	}

	float Time::GetMinutes()const
	{
		return myElapsedTimeInMiliseconds / 1000 / 60 * Modifier;
	}

	float Time::GetSeconds()const
	{
		return myElapsedTimeInMiliseconds / 1000.f * Modifier;
	}

	float Time::GetMiliseconds()const
	{
		return myElapsedTimeInMiliseconds * Modifier;
	}

	float Time::GetMicroseconds()const
	{
		return myElapsedTimeInMiliseconds * 1000 * Modifier;
	}

	void Time::SetModifier(const float aModifier)
	{
		Modifier = aModifier;
	}
}