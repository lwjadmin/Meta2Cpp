#include "MyEngine.h"

int SDL_main(int agrc, char* argv[])
{
	GEngine->Initialize();
	GEngine->Run();
	GEngine->Terminalize();
	delete GEngine;
	system("pause");
	return 0;
}