#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex() : Vertex({ 0, 0 }, {0, 0, 0})
{
}


Vertex::Vertex(const glm::vec2& aPos, const glm::vec3& aColor)
{
	myPos = aPos;
	myColor = aColor;
}

Vertex::~Vertex()
{
}

VkVertexInputBindingDescription Vertex::GetBindingDescription()
{
	VkVertexInputBindingDescription bindingDescription = {};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2> Vertex::GetAttributeDescriptions()
{
	std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, myPos);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, myColor);

	return attributeDescriptions;
}

const glm::vec2 & Vertex::GetPosition() const
{
	return myPos;
}

const glm::vec3& Vertex::GetColor() const
{
	return myColor;
}

void Vertex::SetColor(const glm::vec3& aColor)
{
	myColor = aColor;
}

void Vertex::SetPos(const glm::vec2& aPos)
{
	myPos = aPos;
}
