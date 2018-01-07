#include "RudePenguinEngine\Engine.h"
#include <CommonUtilities\Math\Vector.h>

int main(/*const int argc, const char *argv[]*/)
{
	Engine::Create();

	Vector2i windowSize(800, 600);
	if (Engine::GetInstance().Init(windowSize, true) == false)
	{
		system("pause");
		return 1;
	}


	Engine::GetInstance().StartEngine();
	system("pause");
	return 0;
}
