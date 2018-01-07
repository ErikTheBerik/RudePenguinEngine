#include "CommandLineManager.h"
#include <iostream>

namespace CommonUtilities
{

	std::map<std::string, std::vector<std::string>> CommandLineManager::myArguments;

	CommandLineManager::CommandLineManager()
	{
	}


	CommandLineManager::~CommandLineManager()
	{
	}

	void CommandLineManager::Init(const int argc, const char *argv[])
	{
		std::string level = "-Level";
		std::string car = "-Car";
		std::string ghost = "-Record_Ghost";
		for (int i = 0; i < argc; i++)
		{
			if (std::string(argv[i]) == level)
			{
				if (i + 1 < argc)
				{
					std::string argument = std::string(argv[i + 1]);

					auto &&it = myArguments.find(level);
					if (it != myArguments.end())
					{
						it->second.push_back(argument);
					}
					else
					{
						std::vector<std::string> vec;
						vec.push_back(argument);
						myArguments.emplace(level, vec);
					}
					++i;
				}
				else
				{
					// Error we need argument
				}
			}
			else if (std::string(argv[i]) == car)
			{
				if (i + 1 < argc)
				{
					std::string argument = std::string(argv[i + 1]);

					auto &&it = myArguments.find(car);
					if (it != myArguments.end())
					{
						it->second.push_back(argument);
					}
					else
					{
						std::vector<std::string> vec;
						vec.push_back(argument);
						myArguments.emplace(car, vec);
					}
					++i;
				}
				else
				{
					// Error we need argument
				}
			}
			else if (std::string(argv[i]) == ghost)
			{
				if (i + 1 < argc)
				{
					std::string argument = std::string(argv[i + 1]);

					auto &&it = myArguments.find(ghost);
					if (it != myArguments.end())
					{
						it->second.push_back(argument);
					}
					else
					{
						std::vector<std::string> vec;
						vec.push_back(argument);
						myArguments.emplace(ghost, vec);
					}
					++i;
				}
				else
				{
					// Error we need argument
				}
			}
		}
	}

	bool CommandLineManager::HasParameter(const char *aParameter)
	{
		auto &&it = myArguments.find(aParameter);
		return it != myArguments.end();
	}

	bool CommandLineManager::HasArgument(const char *aParameter, const char *aArgument)
	{
		auto &&it = myArguments.find(aParameter);
		if (it != myArguments.end())
		{
			for (size_t i = 0; i < it->second.size(); i++)
			{
				if (it->second[i] == aArgument)
				{
					return true;
				}
			}
		}
		return false;
	}

	const std::vector<std::string> CommandLineManager::GetArguments(const char * aParameter)
	{
		auto &&it = myArguments.find(aParameter);
		if (it != myArguments.end())
		{
			return it->second;
		}

		return std::vector<std::string>();
	}

}