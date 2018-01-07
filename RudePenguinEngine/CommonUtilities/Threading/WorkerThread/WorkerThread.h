#pragma once
#include "../../Containers/LockedQueue.h"
#include "../WrappedThread/WrappedThread.h"
#include "../Work/Work.h"

namespace CommonUtilities
{
	class WorkerThread
	{
	public:
		WorkerThread();
		~WorkerThread();

		void Stop();
		void Start(const std::string &aName = "Worker Thread");
		void AddWork(const Work &aWork);

	private:
		void Update();
		void Idle();

		LockedQueue<Work> myWorkQueue;
		WrappedThread myThread;
	};
}

namespace CU = CommonUtilities;

