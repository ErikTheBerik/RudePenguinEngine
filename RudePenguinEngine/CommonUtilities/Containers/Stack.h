#pragma once
#include "GrowingArray.h"

namespace CommonUtilities
{
	template <typename T>
	class Stack
	{
	public:
		Stack(const size_t aStartingSize = 10);
		~Stack() = default;

		const T Pop();
		void Push(const T& aObject);

		const T PopObject(const T &aObject);

		bool IsEmpty() const;

		size_t Size() const;

	private:
		GrowingArray<T, size_t> myStack;
	};

	template <typename T>
	const T CommonUtilities::Stack<T>::PopObject(const T &aObject)
	{
		size_t index = myStack.Find(aObject);

		if (index == myStack.FoundNone)
		{
			//DL_PRINT_CONSOLE("Could not find object in stack!", CONSOLE_TEXT_COLOR_RED);
			return aObject;
		}
		myStack.RemoveAtIndex(index);

		return aObject;
		
	}

	template <typename T>
	size_t CommonUtilities::Stack<T>::Size() const
	{
		return myStack.Size();
	}

	template <typename T>
	bool CommonUtilities::Stack<T>::IsEmpty() const
	{
		return myStack.Size() == 0;
	}

	template <typename T>
	void CommonUtilities::Stack<T>::Push(const T& aObject)
	{
		myStack.Add(aObject);
	}

	template <typename T>
	const T CommonUtilities::Stack<T>::Pop()
	{
		T object = myStack.GetLast();
		myStack.RemoveAtIndex(myStack.Size() - 1);
		return object;
	}

	template <typename T>
	CommonUtilities::Stack<T>::Stack(const size_t aStartingSize /*= 10*/)
	{
		myStack.Init(aStartingSize);
	}
}

namespace CU = CommonUtilities;