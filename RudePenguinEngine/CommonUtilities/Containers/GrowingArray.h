#pragma once
#include <assert.h>
#include <cstring>
#include <new>
#include <iostream>


namespace CommonUtilities
{
	template<typename T, typename CountType = size_t>
	class GrowingArray
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin() { return &myArrayPointer[0]; }
		const_iterator begin() const { return &myArrayPointer[0]; }
		iterator end() { return &myArrayPointer[myElementCount]; }
		const_iterator end() const { return &myArrayPointer[myElementCount]; }

		GrowingArray(const CountType aInitialSize = 0);

		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray);

		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);
		GrowingArray& operator=(GrowingArray&& aGrowingArray);

		void Init(CountType aNrOfRecomendedItems);
		void ReInit(CountType aNrOfRecomendedItems);
		inline void SetSize(const CountType aSize);

		inline T &operator[](const CountType& aIndex);
		inline const T &operator[](const CountType& aIndex) const;

		inline void Add(const T & aObject);
		inline void Add(const T && aObject);
		inline void Insert(CountType aIndex, const T & aObject);
		inline void DeleteCyclic(const T & aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const T & aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);
		inline void RemoveAtIndex(CountType aItemNumber);
		inline CountType Find(const T & aObject);

		inline bool IsInRange(const CountType aIndex)const;

		inline T & GetLast();
		inline const T & GetLast() const;
		static const CountType FoundNone = static_cast<CountType>(-1);

		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		__forceinline CountType Size() const;
		inline void Resize(CountType aNewSize);

		inline bool IsInitialized() const;
		inline void SetIsInitialized(const bool aState);

		template<typename TCallback>
		void ForEach(const TCallback &aCallback)
		{
			for (CountType i = static_cast<CountType>(0); i < myElementCount; ++i)
			{
				aCallback((*this)[i]);
			}
		}

		void GrowArray();
		void GrowArray(const CountType aGrowSize);

	private:
		inline void MirrorWithMoveSemantics(GrowingArray && aGrowingArray);
		void DumpAll();

		T *myArrayPointer;
		CountType myElementCount;
		CountType mySizeActual;

		bool myUseSafeMode;
		bool myImInitialized = false;

	};

	template <typename T, typename CountType>
	GrowingArray<typename T, typename CountType>::GrowingArray(const CountType aInitialSize)
	{
		myArrayPointer = nullptr;
		mySizeActual = static_cast<CountType>(0);
		myElementCount = static_cast<CountType>(0);
		myUseSafeMode = ! (std::is_trivially_copyable<T>::value);
		myImInitialized = false;
		if (aInitialSize != 0)
		{
			Init(aInitialSize);
		}
	}

	template <typename T, typename CountType>
	GrowingArray<typename T, typename CountType>::~GrowingArray()
	{
		//assert(myImInitialized == true && "Growing Array is not initialized");

		DumpAll();
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::SetSize(const CountType aSize)
	{
		myElementCount = aSize;
	}

	template <typename T, typename CountType>
	GrowingArray<typename T, typename CountType>::GrowingArray(const GrowingArray& aGrowingArray)
	{
		myArrayPointer = nullptr;
		mySizeActual = static_cast<CountType>(0);
		myElementCount = static_cast<CountType>(0);
		myUseSafeMode = !(std::is_trivially_copyable<T>::value);
		myImInitialized = false;
		(*this) = aGrowingArray;
	}

	template <typename T, typename CountType>
	GrowingArray<typename T, typename CountType>::GrowingArray(GrowingArray&& aGrowingArray)
	{
		MirrorWithMoveSemantics(std::move(aGrowingArray));
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::Init(CountType aNrOfRecomendedItems)
	{
		if (myImInitialized == true)
		{
			std::cout << "Growing array initialized twice!" << std::endl; 
			return;
		}
		assert(myImInitialized == false && "Growing Array should not be initialized twice");
		mySizeActual = aNrOfRecomendedItems;
		myUseSafeMode = !(std::is_trivially_copyable<T>::value);
		myImInitialized = true;

		myArrayPointer = new T[mySizeActual];
	}


	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::ReInit(CountType aNrOfRecomendedItems)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		DumpAll();

		Init(aNrOfRecomendedItems);
	}

	template <typename T, typename CountType>
	GrowingArray<typename T, typename CountType> & GrowingArray<typename T, typename CountType>::operator=(const GrowingArray& aGrowingArray)
	{
		if (myImInitialized != false)
		{
			DumpAll();
		}

		Init(aGrowingArray.mySizeActual);

		
		for (CountType iSlot = 0; iSlot <  aGrowingArray.myElementCount; ++iSlot)
		{
			myArrayPointer[iSlot] = aGrowingArray.myArrayPointer[iSlot];
		}

		myElementCount = aGrowingArray.myElementCount;
		myImInitialized = aGrowingArray.myImInitialized;

		return (*this);
	}

	template <typename T, typename CountType>
	GrowingArray<typename T, typename CountType> & GrowingArray<typename T, typename CountType>::operator=(GrowingArray&& aGrowingArray)
	{
		MirrorWithMoveSemantics(std::move(aGrowingArray));

		return (*this);
	}

	template <typename T, typename CountType>
	T & GrowingArray<typename T, typename CountType>::operator[](const CountType& aIndex)
	{
		//assert(myImInitialized == true && "Growing Array is not initialized");
		//assert(aIndex < myElementCount && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");
		if (myImInitialized == false)
		{
			std::cout << "not inited!";
		}
		return myArrayPointer[aIndex];
	}

	template <typename T, typename CountType>
	const T & GrowingArray<typename T, typename CountType>::operator[](const CountType& aIndex) const
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		assert(aIndex < myElementCount && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");
		if (myImInitialized == false)
		{
			std::cout << "not inited!";
		}
		return myArrayPointer[aIndex];
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::Add(const T & aObject)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");

		if (myElementCount + 1 > (mySizeActual))
		{
			GrowArray();
		}

		myArrayPointer[myElementCount] = aObject;
		++myElementCount;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::Add(const T && aObject)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");

		if (myElementCount + 1 > (mySizeActual))
		{
			GrowArray();
		}

		myArrayPointer[myElementCount] = aObject;
		++myElementCount;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::Insert(CountType aIndex, const T & aObject)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		assert(aIndex <= myElementCount && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be a negative number");

		T tempObject = myArrayPointer[myElementCount - 1];

		if (aIndex != myElementCount)
		{
			for (CountType iData = myElementCount - 1; iData > aIndex; --iData)
			{
				myArrayPointer[iData] = myArrayPointer[iData - 1];
			}
		}
		myArrayPointer[aIndex] = aObject;
		Add(tempObject);
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::DeleteCyclic(const T & aObject)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");

		const CountType ItemSlot = Find(aObject);
		if (ItemSlot != FoundNone)
		{
			DeleteCyclicAtIndex(ItemSlot);
		}
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		assert(aItemNumber < myElementCount && "Index is out of range");
		assert(aItemNumber >= 0 && "Index can not be a negative number");

		if (myElementCount != 1)
		{
			if (aItemNumber == myElementCount - 1)
			{
				delete myArrayPointer[aItemNumber];
				myArrayPointer[aItemNumber] = nullptr;
			}
			else
			{
				delete myArrayPointer[aItemNumber];
				myArrayPointer[aItemNumber] = myArrayPointer[myElementCount - 1];

			}
			--myElementCount;
		}
		else
		{
			delete myArrayPointer[0];
			myArrayPointer[0] = nullptr;
			RemoveAll();
		}
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::RemoveCyclic(const T & aObject)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");

		const CountType ItemSlot = Find(aObject);
		if (ItemSlot != FoundNone)
		{
			RemoveCyclicAtIndex(ItemSlot);
		}
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		if (myElementCount == 0)
		{
			return;
		}

		assert(myImInitialized == true && "Growing Array is not initialized");
		assert(aItemNumber < myElementCount && "Index is out of range");
		assert(aItemNumber >= 0 && "Index can not be a negative number");

		if (myElementCount != 1)
		{
			myArrayPointer[aItemNumber] = myArrayPointer[myElementCount - 1];
			--myElementCount;
		}
		else
		{
			RemoveAll();
		}
	}

	template <typename T, typename CountType>
	void GrowingArray<T, CountType>::RemoveAtIndex(CountType aItemNumber)
	{
		
		if (myElementCount == 0)
		{
			return;
		}
		--myElementCount;
		for (CountType i = aItemNumber; i < myElementCount; ++i)
		{
			myArrayPointer[i] = myArrayPointer[i + 1];
		}
	}

	template <typename T, typename CountType>
	CountType GrowingArray<typename T, typename CountType>::Find(const T & aObject)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");

		for (CountType iSlot = 0; iSlot < myElementCount; ++iSlot)
		{
			if (myArrayPointer[iSlot] == aObject)
			{
				return iSlot;
			}
		}

		return FoundNone;

	}

	template<typename T, typename CountType>
	inline bool GrowingArray<T, CountType>::IsInRange(const CountType aIndex) const
	{
		return aIndex >= 0 && aIndex < myElementCount;
	}

	template <typename T, typename CountType>
	T & GrowingArray<typename T, typename CountType>::GetLast()
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		assert(myElementCount > 0 && "Vector is empty");

		return myArrayPointer[myElementCount - 1];
	}

	template <typename T, typename CountType>
	const T & GrowingArray<typename T, typename CountType>::GetLast() const
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		assert(myElementCount > 0 && "Vector is empty");
		return myArrayPointer[myElementCount - 1];
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::RemoveAll()
	{
		myElementCount = 0;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::DeleteAll()
	{
		if (myElementCount == 0)
		{
			return;
		}

		assert(myImInitialized == true && "Growing Array is not initialized");
		for (CountType iSlot = 0; iSlot < myElementCount; ++iSlot)
		{
			delete myArrayPointer[iSlot];
			myArrayPointer[iSlot] = nullptr;
		}

		RemoveAll();
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::Optimize()
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		if (mySizeActual > myElementCount)
		{
			GrowArray(myElementCount);
		}
	}

	template <typename T, typename CountType>
	CountType GrowingArray<typename T, typename CountType>::Size() const
	{
		//assert(myImInitialized == true && "Growing Array is not initialized");
		return myElementCount;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::Resize(CountType aNewSize)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		while (aNewSize > mySizeActual)
		{
			GrowArray();
		}

		myElementCount = aNewSize;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::MirrorWithMoveSemantics(GrowingArray && aGrowingArray)
	{
		if (myImInitialized != false)
		{
			DumpAll();
		}


		//Init(aGrowingArray.mySizeActual, aGrowingArray.myUseSafeMode);



			
		//for(CountType i = 0; i < aGrowingArray.Size(); i++)
		//{
		//	myArrayPointer[i] = aGrowingArray.myArrayPointer[i];
		//}
		mySizeActual = aGrowingArray.mySizeActual;
		myUseSafeMode = aGrowingArray.myUseSafeMode;

		myArrayPointer = aGrowingArray.myArrayPointer;

		myElementCount = aGrowingArray.myElementCount;
		myImInitialized = aGrowingArray.myImInitialized;


		aGrowingArray.myArrayPointer = nullptr;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::GrowArray()
	{
		assert(myImInitialized == true && "Growing Array is not initialized");
		GrowArray(mySizeActual * 2);
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::GrowArray(const CountType aGrowSize)
	{
		assert(myImInitialized == true && "Growing Array is not initialized");

		if (aGrowSize <= mySizeActual)
			return;

		T* TempPointer = myArrayPointer;
		const CountType TempCount = myElementCount;

		myImInitialized = false;
		Init(aGrowSize);

		if (myUseSafeMode == true)
		{
			for (CountType iSlot = 0; iSlot < TempCount; ++iSlot)
			{
				myArrayPointer[iSlot] = TempPointer[iSlot];
			}
		}
		else
		{
			memcpy(myArrayPointer, TempPointer, (sizeof(T) * TempCount));
		}

		delete[] TempPointer;
		TempPointer = nullptr;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::DumpAll()
	{
		if (myImInitialized == true)
		{
			delete[] myArrayPointer;
			myArrayPointer = nullptr;
			mySizeActual = 0;
		}
		myImInitialized = false;
		RemoveAll();
	}

	template <typename T, typename CountType>
	bool GrowingArray<typename T, typename CountType>::IsInitialized() const
	{
		return myImInitialized;
	}

	template <typename T, typename CountType>
	void GrowingArray<typename T, typename CountType>::SetIsInitialized(const bool aState)
	{
		myImInitialized = aState;
	}
}

namespace CU = CommonUtilities; 