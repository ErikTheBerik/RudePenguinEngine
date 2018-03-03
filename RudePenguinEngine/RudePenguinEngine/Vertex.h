#pragma once
#pragma warning (disable: 4201)
#include <glm/glm.hpp>
#include "vulkan/vulkan.h"
#include <array>

class Vertex
{
public:
	Vertex(const glm::vec3& aPos, const glm::vec3& aColor, const glm::vec2& aCoord);
	Vertex();
	~Vertex();

	static VkVertexInputBindingDescription GetBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions();

	const glm::vec3& GetPosition() const;
	const glm::vec2& GetTextureCoordinates() const;
	const glm::vec3& GetColor() const;

	void SetColor(const glm::vec3& aColor);
	void SetPos(const glm::vec3& aPos);
	void SetTexCoord(const glm::vec2& aCoord);
private:
	glm::vec3 myPos;
	glm::vec2 myTexCoord;
	glm::vec3 myColor;

};

