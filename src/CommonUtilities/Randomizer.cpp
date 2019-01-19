#include "Randomizer.h"
#include <ctime>

namespace CommonUtilities
{
	Randomizer::Randomizer(const size_t seed /*= 0*/)
	{
		int inSeed = static_cast<int>(seed);
		static int ownSeed = 0;
		if (seed == 0)
		{
			inSeed = ownSeed++;
		}
		myRandomizer.seed(static_cast<int>(inSeed));
	}

	Randomizer::~Randomizer()
	{
	}
}