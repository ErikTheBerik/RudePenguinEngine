#pragma once
#include <functional>
template<typename T>
class LockedQueue;

namespace CommonUtilities
{
	class Work
	{
	public:
		Work();
		Work(std::function<void()> aFunction);
		~Work();


		void DoWork();

	private:


		std::function<void()> myFunction;
	};
}
namespace CU = CommonUtilities;


