#pragma once

namespace CommonUtilities
{
	template<typename T>
	struct Lesser
	{
		bool operator()(const T &aLeft, const T &aRight);
	};

	template<typename T>
	bool Lesser<typename T>::operator()(const T &aLeft, const T &aRight)
	{
		return (aLeft < aRight);
	}
}
