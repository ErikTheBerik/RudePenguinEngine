#pragma once
#pragma warning (disable: 4201)
#include <glm/glm.hpp>
#include "vulkan/vulkan.h"
#include <array>

class Vertex
{
public:
	Vertex(const glm::vec2& aPos, const glm::vec3& aColor);
	Vertex();
	~Vertex();

	static VkVertexInputBindingDescription GetBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

	const glm::vec2& GetPosition() const;
	const glm::vec3& GetColor() const;

	void SetColor(const glm::vec3& aColor);
	void SetPos(const glm::vec2& aPos);
private:
	glm::vec2 myPos;
	glm::vec3 myColor;

};

