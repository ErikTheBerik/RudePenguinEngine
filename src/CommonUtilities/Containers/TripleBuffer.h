#pragma once
#include "GrowingArray.h"
namespace CommonUtilities
{
	//Thread safe triple buffer
	template<typename T>
	class TripleBuffer
	{
	public:
		inline TripleBuffer(const size_t aStartingSize = 100);
		inline ~TripleBuffer();

		inline void SwitchWriteBuffers();
		inline void SwitchReadBuffers();
		inline std::vector<T> *GetReadBuffer() const;

		inline void WriteToBuffer(const T& aValue);

	private:
		std::vector<T> myFirstBuffer;
		std::vector<T> mySecondBuffer;
		std::vector<T> myThirdBuffer;

		std::vector<T> *myCurrentWriteBuffer;
		std::vector<T> *myCurrentReadBuffer;
		std::vector<T> *myLatestWrittenBuffer;

		std::mutex myMutex;
	};

	template<typename T>
	void TripleBuffer<T>::WriteToBuffer(const T& aValue)
	{
		myCurrentWriteBuffer->push_back(aValue);
	}

	template<typename T>
	std::vector<T> * TripleBuffer<T>::GetReadBuffer() const
	{
		return myCurrentReadBuffer;
	}

	template<typename T>
	void TripleBuffer<T>::SwitchReadBuffers()
	{
		myMutex.lock();
		auto temp = myCurrentReadBuffer;
		myCurrentReadBuffer = myLatestWrittenBuffer;
		myLatestWrittenBuffer = temp;
		myMutex.unlock();
	}

	template<typename T>
	void TripleBuffer<T>::SwitchWriteBuffers()
	{
		myMutex.lock();
		auto temp = myCurrentWriteBuffer;
		myCurrentWriteBuffer = myLatestWrittenBuffer;
		myLatestWrittenBuffer = temp;
		myMutex.unlock();
		myCurrentWriteBuffer->clear();
	}

	template<typename T>
	TripleBuffer<T>::~TripleBuffer()
	{

	}

	template<typename T>
	TripleBuffer<T>::TripleBuffer(const size_t aStartingSize)
	{
		myFirstBuffer.reserve(aStartingSize);
		mySecondBuffer.reserve(aStartingSize);
		myThirdBuffer.reserve(aStartingSize);
		myCurrentWriteBuffer = &myFirstBuffer;
		myCurrentReadBuffer = &myThirdBuffer;
		myLatestWrittenBuffer = &mySecondBuffer;
	}
}
namespace CU = CommonUtilities;

