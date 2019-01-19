#pragma once
#include <string>
#include <sstream>
#include <stack>
#include <assert.h>

namespace CommonUtilities
{
	//Should be guaranteed to not create any invalid json; will assert when it's used incorrectly
	class JSONWriter
	{
	public:
		JSONWriter();
		~JSONWriter();
		void Begin(const std::string & aFileName);

		void BeginObject(const std::string & aObjectName = "");
		void BeginArray(const std::string & aArrayName = "");

		void EndObject();
		void EndArray();

		inline void WriteMemberString(const std::string & aMemberName, const std::string &aMemberValue);

		template<typename T>
		inline void WriteMember(const std::string & aMemberName, const T &aNumber);


		inline void WriteMemberBool(const std::string & aMemberName, const bool aBool);

		//Only works in arrays
		inline void WriteValueBool(const bool aBool);

		//Only works in arrays
		template<typename T>
		inline void WriteValue(const T &aValue);

		//Only works in arrays
		inline void WriteValueString(const std::string &aMemberValue);

		//Will write to file
		void End();

		void WriteToConsole();

		bool IsInArray();

	private:
		void WriteToFile();
		void BaseEnd();
		std::stack<bool> myIsInArrayStack;
		std::string myFileName = "";
		std::stringstream myContents;
		size_t myNestCount;
	};

	template<typename T>
	inline void JSONWriter::WriteMember(const std::string & aMemberName, const T &aNumber)
	{
		assert(!IsInArray() && "Not currently in object! Can't write member(must be value)");
		static_assert(std::is_pod<T>(), "argument is not a number!");

		myContents << "\"" << aMemberName << "\"";
		myContents << ":";
		myContents << aNumber;
		myContents << ",";
	}

	void JSONWriter::WriteMemberBool(const std::string & aMemberName, const bool aBool)
	{
		assert(!IsInArray() && "Not currently in object! Can't write member(must be value)");
		if (aBool == true)
		{
			myContents << "\"" << aMemberName << "\"";
			myContents << ":";
			myContents << "true";
			myContents << ",";
		}
		else
		{
			myContents << "\"" << aMemberName << "\"";
			myContents << ":";
			myContents << "false";
			myContents << ",";
		}
	}

	void JSONWriter::WriteValueBool(const bool aBool)
	{
		assert(IsInArray() && "Not currently in array! Can't write value(must be member)!");
		if (aBool == true)
		{
			myContents << "true";
			myContents << ",";
		}
		else
		{
			myContents << "false";
			myContents << ",";
		}
	}

	template<typename T>
	void JSONWriter::WriteValue(const T &aValue)
	{
		static_assert(std::is_pod<T>(), "argument is not a number!");
		myContents << std::to_string(aMemberValue);
		myContents << ",";
	}

	void JSONWriter::WriteMemberString(const std::string & aMemberName, const std::string &aMemberValue)
	{
		assert(!IsInArray() && "Not currently in object! Can't write member(must be value)");
		myContents << "\"" << aMemberName << "\"";
		myContents << ":";
		myContents << "\"" << aMemberValue << "\"";
		myContents << ",";
	}

	inline void JSONWriter::WriteValueString(const std::string &aMemberValue)
	{
		assert(IsInArray() && "Not currently in array! Can't write value(must be member)!");
		myContents << "\"" << aMemberValue << "\"";
		myContents << ",";
	}
}

namespace CU = CommonUtilities;