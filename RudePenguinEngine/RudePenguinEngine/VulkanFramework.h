#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>
#include <CommonUtilities\Math\Vector.h>

struct QueueFamilyIndices
{
	bool IsComplete()
	{
		return myGraphicsFamily >= 0
			&& myPresentFamily >= 0;
	}

	int myGraphicsFamily = -1;
	int myPresentFamily = -1;
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR myCapabilities;
	std::vector<VkSurfaceFormatKHR> myFormats;
	std::vector<VkPresentModeKHR> myPresentModes;
};

class VulkanFramework
{
public:
	VulkanFramework();
	~VulkanFramework();

	void Init(const Vector2<int>& aWindowSize, const bool aFullscreen);
	void Cleanup();

	void Update();
	void Close();

	bool ShouldClose();

	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	static void OnWindowResized(GLFWwindow* window, int width, int height);

private:
	void DrawFrame();

	void CleanupSwapChain();

	bool CheckValidationLayerSupport(const std::vector<const char*>& validationLayers);
	bool IsDeviceSuitable(const VkPhysicalDevice& aDevice);
	bool CheckDeviceExtensionSupport(const VkPhysicalDevice& aDevice);
	void GetRequiredExtensions(std::vector<const char*>& requiredExtensions);
	uint32_t RateDevice(const VkPhysicalDevice& deviceToCheck);

	SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device);
	QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& physicalDevice);
	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	void CreateVulkanInstance();
	void SetupDebugCallback();
	void CreateVulkanSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFrameBuffers();
	void CreateCommandPool();
	void CreateVertexBuffers();
	void CreateCommandBuffers();
	void CreateSemaphores();

	void RecreateSwapChain();

	void CreateWindow(const Vector2<int>& aWindowSize, bool aShouldBeFullscreen = false);

private:
	VkInstance myVulkanInstance;
	VkDebugReportCallbackEXT myReportCallback;
	VkPhysicalDevice myPhysicalDevice;
	VkDevice myLogicDevice;
	VkSurfaceKHR myVulkanSurface;

	VkQueue myGraphicsQueue;
	VkQueue myPresentQueue;

	VkSwapchainKHR mySwapChain;
	VkFormat mySwapChainImageFormat;
	VkExtent2D mySwapChainExtent;
	std::vector<VkImage> mySwapChainImages;
	std::vector<VkImageView> mySwapChainImageViews;

	VkRenderPass myRenderPass;
	VkPipelineLayout myPipelineLayout;
	VkPipeline myGraphicsPipeline;

	std::vector<VkFramebuffer> mySwapChainFramebuffers;

	VkBuffer myVertexBuffer;
	VkDeviceMemory myVertexBufferMemory;

	VkCommandPool myCommandPool;
	std::vector<VkCommandBuffer> myCommandBuffers;

	VkSemaphore myImageAvailableSemaphore;
	VkSemaphore myRenderFinishedSemaphore;

	GLFWwindow* myWindow;

	Vector2<int> myWindowSize;
};

