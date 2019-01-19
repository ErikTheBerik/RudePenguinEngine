#include "WorkerThread.h"
#include <functional>
#include <thread>
#include <iostream>

namespace CommonUtilities
{
	WorkerThread::WorkerThread()
	{
		
	}

	WorkerThread::~WorkerThread()
	{
	}

	void WorkerThread::Stop()
	{
		myThread.Stop();
	}

	void WorkerThread::Start(const std::string &aName /*= "Worker Thread"*/)
	{
		myThread.StartFunction(std::function<void()>(std::bind(&WorkerThread::Update, this)), true, aName);
	}

	void WorkerThread::AddWork(const Work &aWork)
	{
		myWorkQueue.Push(aWork);
	}

	void WorkerThread::Update()
	{
		Idle();
		if (myWorkQueue.IsEmpty() == false)
		{
			myWorkQueue.Pop().DoWork();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void WorkerThread::Idle()
	{
		while (myWorkQueue.IsEmpty() == true && myThread.ShouldRun())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

}