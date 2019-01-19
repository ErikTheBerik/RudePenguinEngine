#include "DirtyFileWriter.h"

#include <iostream>
#include <string>

namespace CommonUtilities
{
	DirtyFileWriter::DirtyFileWriter(const std::string &aFilePath)
	{
		myStream.open(aFilePath);
	}

	DirtyFileWriter::~DirtyFileWriter()
	{
		myStream.close();
	}

	void DirtyFileWriter::Write(const std::string &aMessage)
	{
		myStream << aMessage;
	}

	void DirtyFileWriter::WriteLine(const std::string &aMessage)
	{
		myStream << aMessage << std::endl;
	}
}