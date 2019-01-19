#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#define CONSOLE_TEXT_COLOR_RED 12
#define CONSOLE_TEXT_COLOR_YELLOW 14
#define CONSOLE_TEXT_COLOR_GREEN 10
#define CONSOLE_TEXT_COLOR_WHITE 15
#define DL_ASSERT(string)string;
#define DL_PRINT(string) string;
#define DL_DEBUG( ... );

#define DL_PRINT_CONSOLE(string, color)string;color;
//#else
//#define DL_ASSERT(string) DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__, string);
//#define DL_PRINT(string)  DL_Debug::Debug::GetInstance()->PrintMessage(string);
//#define DL_DEBUG( ... )  DL_Debug::Debug::GetInstance()->DebugMessage(__LINE__,__FUNCTION__,__VA_ARGS__);
//
//#define DL_PRINT_CONSOLE(string, color) DL_Debug::Debug::GetInstance()->PrintConsole(string, color);
//#endif


#define DL_WRITELOG(log, ...)  DL_Debug::Debug::GetInstance()->WriteLog(log,__VA_ARGS__);

namespace std
{
	class mutex;
}

namespace DL_Debug
{
	class Debug
	{
	public:
		friend class MainSingleton;
		enum class LogType
		{
			Resource = 0,
			Game,
			Engine,
			HeavyModel,
			Sound,
			length
		};
		static bool Create(std::string aFile = "Debug_Logger/DebugLogger.txt");
		static bool Destroy();
		void SetIsModelViewer(bool aIsModelViewer);
		bool GetIsModelViewer()const;
		static Debug* GetInstance();
		void AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aString);
		void PrintMessage(const char *aString);
		void DebugMessage(const int aLine, const char *aFunction, const char *aFormattedString, ...);
		void PrintConsole(const char* aText, const int& aColor);
		static std::string GetCurrentTimeAsString(const char * aFormat);
		void WriteLog(const char* aLogName, const char *aFormattedString, ...);
		static void ActivateFilterlog(LogType aLogType);
		static void DeactivateFilterlog(LogType aLogType);
		static const char* GetString(LogType aLogType);
	private:
		Debug(std::string aFile = "Debug_Logger/DebugLogger.txt");
		~Debug();
		void SetConsoleColor(const int& aColor);
		static Debug* ourInstance;
		std::ofstream myDebugFile;
		std::ofstream myLogFile;
		std::string myTimeName;
		static std::vector<const char*> myLogStrings;
		static std::map<LogType, bool> myLogs;
		std::mutex *myMutex;
		bool myIsModelViewer;
	};
}