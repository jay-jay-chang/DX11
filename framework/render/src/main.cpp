////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "framework.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Framework* framework;
	bool result;
	
	
	// Create the system object.
	framework = new Framework();
	if(!framework)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = framework->Initialize();
	if(result)
	{
		framework->Run();
	}

	// Shutdown and release the system object.
	framework->Shutdown();
	delete framework;
	framework = NULL;

	return 0;
}