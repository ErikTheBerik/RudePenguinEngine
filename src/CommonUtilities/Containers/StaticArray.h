#pragma once
#include <assert.h>

namespace CommonUtilities
{
	//template class StaticArray<int*, 10>;
	template <typename Type, int Size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);

		~StaticArray();

		StaticArray& operator=(const StaticArray& aStaticArray);

		inline const Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);


		// Utility functions
		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();
		inline int GetSize()
		{
			return mySize;
		}
	private:
		Type myArray[Size];
		int mySize;
	};

	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray()
	{
		mySize = Size;
	}

	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray(const StaticArray& aStaticArray)
	{
		*this = aStaticArray;
		mySize = Size;
	}

	template <typename Type, int Size>
	StaticArray<Type, Size>::~StaticArray()
	{

	}

	template <typename Type, int Size>
	StaticArray<Type, Size>& StaticArray<Type, Size>::operator=(const StaticArray& aStaticArray)
	{
		for (int i = 0; i < Size; i++)
		{
			myArray[i] = aStaticArray.myArray[i];
		}
		mySize = Size;
		return *this;
	}

	template <typename Type, int Size>
	const Type& StaticArray<Type, Size>::operator[](const int& aIndex) const
	{
		assert((aIndex >= 0 && aIndex < Size) && "Subscript out of bounds");
		return myArray[aIndex];
	}

	template <typename Type, int Size>
	Type& StaticArray<Type, Size>::operator[](const int& aIndex)
	{
		assert((aIndex >= 0 && aIndex < Size) && "Subscript out of bounds");
		return myArray[aIndex];
	}

	template<typename Type, int Size>
	void StaticArray<Type, Size>::Insert(int aIndex, Type& aObject)
	{
		assert((aIndex >= 0 && aIndex < Size) && "Array out of bounds");
		for (int i = Size -1; i > aIndex; i--)
		{
			myArray[i] = myArray[i - 1];
		}
		myArray[aIndex] = aObject;
	}

	template<typename Type, int Size>
	void StaticArray<Type, Size>::DeleteAll()
	{
		for (int i = 0; i < Size; i++)
		{
			delete myArray[i];
			myArray[i] = nullptr;
		}
	}
}

namespace CU = CommonUtilities;