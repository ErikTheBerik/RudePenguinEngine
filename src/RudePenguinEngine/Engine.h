#pragma once
#include <functional>
#include <CommonUtilities/glm/vec2.hpp>

class VulkanFramework;

class Engine
{
public:
	friend class MainSingleton;
	static Engine &GetInstance();

	static bool IsEngineCreated();
	static void Create();

	bool Init(const glm::vec2& aWindowSize, const bool aFullscreen, std::function<void()> aGameUpdateFunction = nullptr, std::function<void()> aGameDrawFunction = nullptr, std::function<void()> aGameDebugFunction = nullptr);
	
	void StartThreads();
	void StartEngine();

	void Update();
	void Draw();

	void CloseEngine();
	void ShutDown();

	void PauseGame();
	void ResumeGame();

private:
	Engine();
	~Engine();

	void Cleanup();
	static Engine* ourInstance;

	std::function<void()> myGameUpdateFunction;
	std::function<void()> myGameDrawFunction;
	std::function<void()> myGameDebugFunction;

	bool myGamePaused;
	bool myShouldRun;

	VulkanFramework* myVulkanFramework;

};

