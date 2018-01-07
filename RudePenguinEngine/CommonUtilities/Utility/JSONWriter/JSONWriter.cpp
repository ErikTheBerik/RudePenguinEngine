#include "JSONWriter.h"
#include "DirtyFileWriter.h"
#include <iostream>

namespace CommonUtilities
{
	JSONWriter::JSONWriter()
	{
		myFileName = "";
		myNestCount = 0;
	}

	JSONWriter::~JSONWriter()
	{
	}

	void JSONWriter::Begin(const std::string & aFileName)
	{
		myFileName = aFileName;
		myContents << "{\n";
		myIsInArrayStack.push(false);
	}

	void JSONWriter::BeginObject(const std::string & aObjectName /*= ""*/)
	{
		if (aObjectName != "")
		{
			assert(!IsInArray() && "object must be named when not in array!");
			myContents << "\"" << aObjectName << "\"" << " : ";
		}
		myContents << "{\n";
		myIsInArrayStack.push(false);
		myNestCount++;
	}

	void JSONWriter::BeginArray(const std::string & aArrayName)
	{
		if (aArrayName == "")
		{
			assert(IsInArray() && "Array can only be unnamed when in another array!");
			myContents << "[ ";
		}
		else
		{
			assert(!IsInArray() && "Array must be unnamed when in another array!");
			myContents << "\"" << aArrayName << "\"" << " : " << "[ ";
		}
		myIsInArrayStack.push(true);
		myNestCount++;
	}

	void JSONWriter::EndObject()
	{
		assert(!IsInArray() && "Tried to end object when in array!");
		BaseEnd();
		myContents << "},";
		myNestCount--;
	}

	void JSONWriter::EndArray()
	{
		assert(IsInArray() && "Tried to end array when in object!");
		BaseEnd();
		myContents << "],";
		myNestCount--;
	}

	void JSONWriter::End()
	{
		BaseEnd();
		myContents << "}\n";
		assert(myNestCount == 0 && "Some objects or arrays are not ended!");
		WriteToFile();
		myContents.clear();
		myContents.str("");
	}

	void JSONWriter::WriteToConsole()
	{
		std::cout << myContents.str();
	}

	bool JSONWriter::IsInArray()
	{
		return myIsInArrayStack.top();
	}

	void JSONWriter::WriteToFile()
	{
		DirtyFileWriter writer(myFileName);

		writer.Write(myContents.str());
	}

	void JSONWriter::BaseEnd()
	{
		myIsInArrayStack.pop();
		//will move character pointer one step to the left; next character will overwrite a ','
		myContents.seekp(-1, std::ios_base::end);
	}
}