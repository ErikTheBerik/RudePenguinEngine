#pragma once
namespace CommonUtilities
{
	class Time
	{
	public:
		Time();
		~Time();
		void AddTime(float aTime);
		void SetTime(float aTime);
		float GetHours()const;
		float GetMinutes()const;
		float GetSeconds()const;
		float GetMiliseconds()const;
		float GetMicroseconds() const;
		void SetModifier(const float aModifier);
	private:
		float myElapsedTimeInMiliseconds;
		static float Modifier;
	};
}

namespace CU = CommonUtilities;