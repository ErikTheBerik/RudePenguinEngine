#include "RudePenguinEngine\Engine.h"
#include <CommonUtilities\glm\vec2.hpp>

int main(/*const int argc, const char *argv[]*/)
{
	Engine::Create();

	glm::vec2 windowSize(800, 600);
	if (Engine::GetInstance().Init(windowSize, true) == false)
	{
		system("pause");
		return 1;
	}


	Engine::GetInstance().StartEngine();
	system("pause");
	return 0;
}
