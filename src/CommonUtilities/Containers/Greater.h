#pragma once

namespace CommonUtilities
{
	template<typename T>
	struct Greater
	{
		inline bool operator()(const T &aLeft, const T &aRight);
	};

	template<typename T>
	bool Greater<typename T>::operator()(const T &aLeft, const T &aRight)
	{ 
		return (aLeft > aRight); 
	}
}
