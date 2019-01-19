#pragma once
#include <map>
#include <vector>
#include <string>

namespace CommonUtilities
{
	class CommandLineManager
	{
	public:
		CommandLineManager();
		~CommandLineManager();

		static void Init(const int argc, const char *argv[]);
		static bool HasParameter(const char *aParameter);
		static bool HasArgument(const char *aParameter, const char *aArgument);
		static const std::vector<std::string> GetArguments(const char *aParameter);
	private:
		static std::map<std::string, std::vector<std::string>> myArguments;
	};
}
namespace CU = CommonUtilities;