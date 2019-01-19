#pragma once
#pragma warning (disable: 4201)
#include <CommonUtilities/glm/glm.hpp>
#include "vulkan/vulkan.h"
#include <array>

#define GLM_ENABLE_EXPERIMENTAL
#include <CommonUtilities/glm/gtx/hash.hpp>

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

	inline bool operator==(const Vertex& other) const 
	{
		return myPos == other.myPos && myColor == other.myColor && myTexCoord == other.myTexCoord;
	}

private:
	glm::vec3 myPos;
	glm::vec2 myTexCoord;
	glm::vec3 myColor;

};

namespace std
{
	template<> struct hash<Vertex>
	{
		size_t operator()(Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.GetPosition()) ^
				(hash<glm::vec3>()(vertex.GetColor()) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.GetTextureCoordinates()) << 1);
		}
	};
}
