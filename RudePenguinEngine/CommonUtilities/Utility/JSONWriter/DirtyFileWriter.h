#pragma once
#include <fstream>

namespace CommonUtilities
{
	class DirtyFileWriter
	{
	public:
		DirtyFileWriter(const std::string &aFilePath);
		~DirtyFileWriter();

		void Write(const std::string &aMessage);
		void WriteLine(const std::string &aMessage);
	private:
		std::ofstream myStream;
	};
}

namespace CU = CommonUtilities;