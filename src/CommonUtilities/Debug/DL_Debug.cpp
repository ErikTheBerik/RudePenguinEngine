#include "DL_Debug.h"
#include <assert.h>
#include <cstdarg>
#include "DL_StackWalker.h"
#include <sstream>
#include "DL_Assert.h"
#include <stdio.h>
#include <stdarg.h>
#include <ctime>
#include "Utility/CommandLineManager.h"
#include <mutex>


std::vector<const char*> DL_Debug::Debug::myLogStrings;
std::map<DL_Debug::Debug::LogType, bool> DL_Debug::Debug::myLogs;

namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;

	Debug::Debug(std::string aFile)
	{
		myIsModelViewer = false;
		myMutex = new std::mutex();

		//myDebugFile->open(aFile);
		myDebugFile.open(aFile, std::ofstream::out);
		if (myDebugFile.is_open() == false || myDebugFile.bad() == true || !myDebugFile)
		{
			std::cout << "file not open" << std::endl;
		}
		
	}

	Debug::~Debug()
	{
		if (myDebugFile.is_open() == true)
		{
			ourInstance->myDebugFile.close();
		}
		
		ourInstance->myLogFile.close();
	}

	void Debug::SetConsoleColor(const int & aColor)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole == nullptr)
		{
			return;
		}

		SetConsoleTextAttribute(hConsole, static_cast<WORD>(aColor));
	}

	bool Debug::Create(std::string aFile)
	{
		//aFile;
		assert(ourInstance == nullptr && "Debugobject already created");
		ourInstance = new Debug();
		
		
		ourInstance->myTimeName = GetCurrentTimeAsString("%d-%m-%Y_%I-%M-%S");

		myLogStrings.push_back("Resource");
		myLogStrings.push_back("Game");
		myLogStrings.push_back("Engine");
		myLogStrings.push_back("HeavyModel");
		myLogStrings.push_back("Sound");

		for (int i = 0; i < static_cast<int>(Debug::LogType::length);i++)
		{
			myLogs.emplace(static_cast<LogType>(i), false);
		}

		for (int i = 0; i < static_cast<int>(Debug::LogType::length); i++)
		{
			if (CU::CommandLineManager::HasArgument("-activatelog", myLogStrings[i]))
			{
				myLogs.find(static_cast<LogType>(i))->second = true;
			}
		}

		if (ourInstance == nullptr)
		{
			return(false);
		}
		return(true);
	}

	bool Debug::Destroy()
	{
		if (ourInstance->myDebugFile.is_open() == true)
		{
			DL_ASSERT("Manual assert to force callstack");
			
		}
		//SAFE_DELETE(ourInstance);
		delete ourInstance;
		ourInstance = nullptr;
		return true;
	}

	void Debug::SetIsModelViewer(bool aIsModelViewer)
	{
		myIsModelViewer = aIsModelViewer;
	}

	bool Debug::GetIsModelViewer() const
	{
		return myIsModelViewer;
	}

	Debug* Debug::GetInstance()
	{
		return(ourInstance);
	}

	void Debug::AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aString)
	{
		std::string test = "";
		DL_Debug::StackWalker stack;

		ourInstance->myDebugFile << "Crash in file: " << aFileName << std::endl;
		ourInstance->myDebugFile << "Line: " << aLine << std::endl;
		ourInstance->myDebugFile << "In function: " << aFunctionName << std::endl;
		ourInstance->myDebugFile << aString << "\n" << std::endl;
		ourInstance->myDebugFile << stack.ShowCallstack() << std::endl;


		std::wstringstream message;
		message << aString;

		std::wstringstream file;
		file << aFileName;

		ourInstance->myDebugFile.close();
		
 		_wassert(message.str().c_str(), file.str().c_str(), aLine);
	}
	
	void Debug::PrintMessage(const char *aString)
	{
		ourInstance->myDebugFile << aString << std::endl;
	}

	void Debug::DebugMessage(const int aLine, const char *aFunction, const char *aFormattedString, ...)
	{

		ourInstance->myDebugFile << "File name: " << aFunction << std::endl;
		ourInstance->myDebugFile << "Line: " << aLine << std::endl;

		char buffer[256];
		va_list args;
		va_start(args, aFormattedString);
		vsprintf_s(buffer, aFormattedString, args);
		perror(buffer);
		va_end(args);

		ourInstance->myDebugFile << aFormattedString << " " << buffer << std::endl;
		
	}

	void Debug::PrintConsole(const char * aText, const int & aColor)
	{
		if (myIsModelViewer == false)
		{
			if (aColor == 15)
			{
				return;
			}
			myMutex->lock();
			SetConsoleColor(aColor);
			aText;
			std::cout << aText << std::endl;
			SetConsoleColor(CONSOLE_TEXT_COLOR_WHITE);
			myMutex->unlock();
		}
	}


	std::string Debug::GetCurrentTimeAsString(const char *aFormat)
	{
		time_t rawtime = time(0);

		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);

#pragma warning ( disable : 4996 )
		timeinfo = localtime(&rawtime);
#pragma warning ( default : 4996 )

		strftime(buffer, 80, aFormat, timeinfo);
		std::string str(buffer);

		return str;
	}

	void Debug::WriteLog(const char* aLogName, const char *aFormattedString, ...)
	{		
		for (size_t i = 0; i < myLogStrings.size(); ++i)
		{
			if (myLogStrings[i] == aLogName)
			{
				if (myLogs.find(static_cast<LogType>(i))->second == true)
				{
					std::string name = aLogName;
					std::string filePath = "Logs/" + myTimeName + " " + name + ".log";
					myLogFile.open(filePath, std::ios_base::app);
					aFormattedString;
					myLogFile << "[" << GetCurrentTimeAsString("%I:%M:%S") << "] " << aFormattedString << std::endl;
					myLogFile.close();
				}
			}
		}

		ourInstance->myDebugFile << aFormattedString << "\n";
	}


	void Debug::ActivateFilterlog(LogType aLogType)
	{
		auto &&it = GetInstance()->myLogs.find(aLogType);
		if (it != GetInstance()->myLogs.end())
		{
			it->second = true;
		}
	}

	void Debug::DeactivateFilterlog(LogType aLogType)
	{
		auto &&it = GetInstance()->myLogs.find(aLogType);
		if (it != GetInstance()->myLogs.end())
		{
			it->second = false;
		}
	}

	const char* Debug::GetString(LogType aLogType)
	{
		return myLogStrings[static_cast<int>(aLogType)];
	}
}