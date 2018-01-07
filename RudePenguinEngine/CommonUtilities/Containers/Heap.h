#pragma once
#include "Greater.h"
#include "Lesser.h"
#include "PointerLesser.h"
#include "GrowingArray.h"
#pragma warning (disable : 4267)

/*

												  root at 0    root at 1
								Left child        ix * 2 + 1     ix * 2
								Right child       ix * 2 + 2     ix * 2 + 1
								Parent			  (ix - 1) / 2     ix / 2
 
*/

namespace CommonUtilities
{
	template<typename T, typename Comparer = Greater<T>>
	class Heap
	{
	public:
		inline Heap(CommonUtilities::GrowingArray<T> aGrowingArray = CommonUtilities::GrowingArray<T>());
		~Heap();
		inline void Enqueue(T someData);
		inline T Dequeue();
		inline bool IsEmpty();
		inline void Printudes();
	private:
		Comparer myComparer;
		CommonUtilities::GrowingArray<T> myData;
		inline void Floyds();
		inline void Swap(int aLeftIndex, int aRightIndex);
		inline T Max(int aLeftIndex, int aRightIndex);
		inline T Min(int aLeftIndex, int aRightIndex);
	};


	template <typename T, typename Comparer>
	Heap<typename T, typename Comparer>::Heap(CommonUtilities::GrowingArray<T> aGrowingArray)
	{
		if (aGrowingArray.IsInitialized() == false)
		{
			aGrowingArray.Init(4);
			myData = aGrowingArray;
		}
		else
		{
			myData = aGrowingArray;

			Floyds();
		}
	}
		

	template <typename T, typename Comparer>
	Heap<typename T, typename Comparer>::~Heap()
	{
		
	}

	template <typename T, typename Comparer>
	void Heap<typename T, typename Comparer>::Enqueue(T someData)
	{
		myData.Add(someData);

		unsigned pos = (unsigned)(myData.Size() - 1);

		while ((pos > 0) && myComparer(myData[pos], myData[(pos - 1) / 2]))
		{
			Swap((pos - 1) / 2, pos);
			pos = (pos - 1) / 2;
		}
	}

	template<typename T, typename Comparer>
	T Heap<typename T, typename Comparer>::Dequeue(void)
	{
		if (IsEmpty() == true)
		{
			assert(false);
		}

		T originalRoot = myData[0];
		myData[0] = myData[myData.Size() - 1];
		myData.RemoveCyclicAtIndex(myData.Size() - 1);


		int leafLevel = (myData.Size() - 1) / 2;
		int pos = 0;
		int leftChild = pos * 2 + 1;
		int rightChild = pos * 2 + 2;

		while ((pos <= leafLevel) && (leftChild < myData.Size() || rightChild < myData.Size()))
		{
			if (rightChild < myData.Size() && (myComparer(myData[leftChild], myData[pos]) || myComparer(myData[rightChild], myData[pos])))
			{
				if (myComparer(myData[leftChild], myData[rightChild]) && myComparer(myData[leftChild], myData[pos]))
				{
					Swap(pos, leftChild);
					pos = leftChild;
					leftChild = pos * 2 + 1;
					rightChild = pos * 2 + 2;
				}
				else if (myComparer(myData[rightChild], myData[pos]))
				{
					Swap(pos, rightChild);
					pos = rightChild;
					rightChild = pos * 2 + 2;
					leftChild = pos * 2 + 1;
				}
				else
				{
					break;
				}
			}
			else if (leftChild < myData.Size())
			{
				if (myComparer(myData[leftChild], myData[pos]))
				{
					Swap(pos, leftChild);
					pos = leftChild;
					leftChild = pos * 2 + 1;
					rightChild = pos * 2 + 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		return originalRoot;
	}


	template<typename T, typename Comparer>
	void Heap<typename T, typename Comparer>::Printudes()
	{
		for (int i = 0; i < myData.Size(); i++)
		{
			std::cout << myData[i] << std::endl;
		}
	}

	template<typename T, typename Comparer>
	void Heap<typename T, typename Comparer>::Swap(int aLeftIndex, int aRightIndex)
	{
		T temp = myData[aLeftIndex];

		myData[aLeftIndex] = myData[aRightIndex];
		myData[aRightIndex] = temp;
	}

	template<typename T, typename Comparer>
	T Heap<typename T, typename Comparer>::Max(int aLeftIndex, int aRightIndex)
	{
		if (myData[aLeftIndex] > myData[aRightIndex])
		{
			return aLeftIndex;
		}
		return aRightIndex;
	}

	template<typename T, typename Comparer>
	T Heap<typename T, typename Comparer>::Min(int aLeftIndex, int aRightIndex)
	{
		if (myData[aLeftIndex] < myData[aRightIndex])
		{
			return aLeftIndex;
		}
		return aRightIndex;
	}

	template<typename T, typename Comparer>
	bool Heap<typename T, typename Comparer>::IsEmpty()
	{
		return myData.Size() <= 0;
	}

	template <typename T, typename Comparer>
	void Heap<typename T, typename Comparer>::Floyds()
	{
		int lastNonLeafIndex = myData.Size() / 2 - 1;
		
		for (int i = lastNonLeafIndex; i >= 0; --i)
		{
			//MoveDown(myData (data), i(first), size-1(last))
			int first = i;
			int last = myData.Size() - 1;
			int largest = 2 * first + 1;

			while (largest <= last)
			{
				if (largest < last && myComparer(myData[largest + 1], myData[largest]))
				{
					largest++;
				}
				if (myComparer(myData[largest], myData[first]))
				{
					Swap(first, largest);
					first = largest;
					largest = 2 * first + 1;
				}
				else
				{
					largest = last + 1;
				}
			}

		}
	}
}
#pragma warning (default : 4267)