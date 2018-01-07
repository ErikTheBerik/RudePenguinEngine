#pragma once
#include <functional>
#include <atomic>
#include <string>
#include <memory>

namespace std
{
	class thread;
}

namespace CommonUtilities
{
	class WrappedThread
	{
	public:
		WrappedThread();
		~WrappedThread();

		void StartFunction(const std::function<void()> &aFunction, bool aRunContinuously, const std::string &aName);

		//will wait for function to end and set it to end(if it's run continously)
		void Stop();

		bool IsRunning() const;

		bool ShouldRun() const;
		void Pause();

		void Unpause();

	private:
		void RunFunction();
		std::shared_ptr<std::function<void()>> myFunction;
		std::unique_ptr<std::thread> myThread;
		std::atomic<bool> myRunFunction;
		std::atomic<bool> myPaused;
		std::string myName;
	};
}