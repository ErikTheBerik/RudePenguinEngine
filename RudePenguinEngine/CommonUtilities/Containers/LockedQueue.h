#pragma once
#include <atomic>
#include <thread>
#include <mutex>

namespace CommonUtilities
{
	//threadsafe(write and read) queue.
	//when you make a lockless queue and have to add locks and they ask you how you are and you just have to say you're fine when you're not really fine
	//Size is actually one less than what you assign it cause I'm a bad programmer
	template<typename T, size_t Size = 2000>
	class LockedQueue
	{
	public:
		inline LockedQueue();
		inline ~LockedQueue();

		inline void Push(const T& aValue);
		inline T Pop();

		inline bool IsEmpty() const;
		inline bool IsFull() const;

	private:
		inline void AddWriteIndex();
		inline void AddReadIndex();
		T *myData;
		std::atomic<size_t> myCurrentWriteIndex;
		std::atomic<size_t> myCurrentReadIndex;
		std::mutex myReadMutex;
		std::mutex myWriteMutex;
	};

	template <typename T, size_t Size>
	inline LockedQueue<T, Size>::LockedQueue()
	{
		myCurrentReadIndex = 0;
		myCurrentWriteIndex = 0;
		myData = new T[Size];
	}

	template <typename T, size_t Size>
	inline LockedQueue<T, Size>::~LockedQueue()
	{
		delete[] myData;
	}

	template <typename T, size_t Size>
	inline void LockedQueue<T, Size>::Push(const T& aValue)
	{
		while (IsFull())
		{
			//look this should not really happen dude. It slows everything down like craaaaaaaaazyyy
			std::cout << "NO" << std::endl;
			//DL_PRINT_CONSOLE("SHOULD NOT HAPPEN", CONSOLE_TEXT_COLOR_RED);
			std::this_thread::yield();
		}

		myWriteMutex.lock();
		myData[myCurrentWriteIndex] = aValue;
		AddWriteIndex();
		myWriteMutex.unlock();
	}

	template <typename T, size_t Size>
	inline T LockedQueue<T, Size>::Pop()
	{
		while (IsEmpty())
		{
			//look this should not really happen dude. It slows everything down like craaaaaaaaazyyy
			std::this_thread::yield();
		}
		myReadMutex.lock();
		T data = myData[myCurrentReadIndex];
		AddReadIndex();
		myReadMutex.unlock();
		return data;
	}

	template <typename T, size_t Size>
	inline bool LockedQueue<T, Size>::IsEmpty() const
	{
		return myCurrentReadIndex == myCurrentWriteIndex;
	}

	template <typename T, size_t Size>
	inline bool LockedQueue<T, Size>::IsFull() const
	{
		return myCurrentReadIndex == (myCurrentWriteIndex + 1) % (Size);
	}

	template <typename T, size_t Size>
	inline void LockedQueue<T, Size>::AddWriteIndex()
	{
		++myCurrentWriteIndex;
		if (myCurrentWriteIndex == Size)
		{
			myCurrentWriteIndex = 0;
		}
	}


	template <typename T, size_t Size>
	inline void LockedQueue<T, Size>::AddReadIndex()
	{
		++myCurrentReadIndex;
		if (myCurrentReadIndex == Size)
		{
			myCurrentReadIndex = 0;
		}
	}
}
namespace CU = CommonUtilities;