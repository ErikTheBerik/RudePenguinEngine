#pragma once
#include <random>

namespace CommonUtilities
{
	class Randomizer
	{
	public:
		Randomizer(const size_t seed = 0);
		~Randomizer();

		template<typename T>
		T GetValue();

		template<typename T>
		T GetValue(const T aMax);

		template<typename T>
		T GetValue(const T aMin, const T aMax);

		template<typename T = float>
		T GetFloatValue();

		template<typename T = float>
		T GetFloatValue(const T aMax);

		template<typename T = float>
		T GetFloatValue(const T aMin, const T aMax);

	private:
		std::mt19937 myRandomizer;
		const unsigned int MinimumRandom = 0;
		const unsigned int MaximumRandom = UINT_MAX;
	};

	template<typename T>
	T Randomizer::GetValue()
	{
		static_assert(std::is_integral<T>::value, "Randomizer::GetValue() template argument not integral! If you want to get a floating point number, use Randomizer::GetFloatValue!");

		return static_cast<T>(myRandomizer());
	}

	template<typename T>
	T Randomizer::GetValue(const T aMax)
	{
		static_assert(std::is_integral<T>::value, "Randomizer::GetValue() template argument not integral! If you want to get a floating point number, use Randomizer::GetFloatValue!");
		auto value = GetValue<T>();

		if (value < static_cast<T>(0))
		{
			value = std::abs(value);
		}

		return value % aMax;
	}


	template<typename T>
	T Randomizer::GetValue(const T aMin, const T aMax)
	{
		static_assert(std::is_integral<T>::value, "Randomizer::GetValue() template argument not integral! If you want to get a floating point number, use Randomizer::GetFloatValue!");
		auto value = GetValue<T>(aMax - aMin);
		value += aMin;
		return value;
	}

	template<typename T>
	T Randomizer::GetFloatValue()
	{
		static_assert(std::is_floating_point<T>::value, "Randomizer::GetValue() template argument not floating point! If you want to get an integral number, use Randomizer::GetValue!");

		return static_cast<T>(myRandomizer());
	}

	template<typename T>
	T Randomizer::GetFloatValue(const T aMax)
	{
		static_assert(std::is_floating_point<T>::value, "Randomizer::GetValue() template argument not floating point! If you want to get an integral number, use Randomizer::GetValue!");
		auto value = GetFloatValue<T>();

		if (value < static_cast<T>(0))
		{
			value = std::fabs(value);
		}

		return (value / static_cast<T>(MaximumRandom)) * aMax;
	}


	template<typename T>
	T Randomizer::GetFloatValue(const T aMin, const T aMax)
	{
		static_assert(std::is_floating_point<T>::value, "Randomizer::GetValue() template argument not floating point! If you want to get an integral number, use Randomizer::GetValue!");
		auto value = GetFloatValue<T>(aMax - aMin);
		value += aMin;
		return value;
	}
}

namespace CU = CommonUtilities;