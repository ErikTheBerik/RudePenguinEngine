#include "stdafx.h"
#include "Engine.h"

#include "VulkanFramework\VulkanFramework.h"

#include <CommonUtilities\Time\TimeManager.h>
#include <CommonUtilities\glm\mat4x4.hpp>
#include <CommonUtilities\Threading\WrappedThread\WrappedThread.h>

Engine* Engine::ourInstance = nullptr;

Engine &Engine::GetInstance()
{
	return *ourInstance;
}

bool Engine::IsEngineCreated()
{
	return ourInstance != nullptr;
}

void Engine::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Engine();
	}
}

bool Engine::Init(const glm::vec2& aWindowSize, const bool aFullscreen, std::function<void()> aGameUpdateFunction /*= nullptr*/, std::function<void()> aGameDrawFunction /*= nullptr*/, std::function<void()> aGameDebugFunction /*= nullptr*/)
{
	myGamePaused = false;
	myGameUpdateFunction = aGameUpdateFunction;
	myGameDrawFunction = aGameDrawFunction;
	myGameDebugFunction = aGameDebugFunction;

	myVulkanFramework = new VulkanFramework();
	myVulkanFramework->Init(aWindowSize, aFullscreen);

	return true;
}

void Engine::StartThreads()
{
#ifdef THREADED_RENDERING
	MainSingleton::GetThreadManager()->Init(std::bind(&Engine::Draw, this));
#endif
}

void Engine::Update()
{
	while (myShouldRun)
	{
		myVulkanFramework->Update();

		if (myGamePaused == false)
		{
			if (myGameUpdateFunction != nullptr)
			{
				myGameUpdateFunction();
				Draw();
			}
		}

		if (myVulkanFramework->ShouldClose())
		{
			myShouldRun = false;
		}
	}

	myVulkanFramework->Close();
}

void Engine::Draw()
{
	if (myGamePaused == false)
	{
		if (myGameDrawFunction != nullptr)
		{
			myGameDrawFunction();
		}
	}
}

void Engine::StartEngine()
{
	Update();
	ShutDown();
}

void Engine::CloseEngine()
{
	exit(0);
}

void Engine::PauseGame()
{
	myGamePaused = true;
}

void Engine::ResumeGame()
{
	myGamePaused = false;
}

void Engine::ShutDown()
{
	myShouldRun = false;
	Cleanup();
}

void Engine::Cleanup()
{
	myVulkanFramework->Cleanup();
}

Engine::Engine()
{
	myGamePaused = false;
	myShouldRun = true;

	myGameDebugFunction = nullptr;
	myGameDrawFunction = nullptr;
	myGameUpdateFunction = nullptr;
}

Engine::~Engine()
{
	Cleanup();
}