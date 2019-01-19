#pragma once

namespace CommonUtilities
{
	template<typename T>
	struct PointerLesser
	{
		bool operator()(const T aLeft, const T aRight);
	};

	template<typename T>
	bool PointerLesser<typename T>::operator()(const T aLeft, const T aRight)
	{
		return ((*aLeft) < (*aRight));
	}
}
