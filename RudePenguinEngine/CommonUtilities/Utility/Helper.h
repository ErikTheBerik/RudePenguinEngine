#pragma once
#include <vector>
#include <fstream>

static inline void readFile(const std::string& filename, std::vector<char>& result)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) 
	{
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	result.resize(fileSize);

	file.seekg(0);
	file.read(result.data(), fileSize);

	file.close();

}