////////////////////////////////////////////////////////////////////////////////
// Filename: Framework.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Framework_H_
#define _Framework_H_


//////////////
// INCLUDES //
//////////////
#include <windows.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Input.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Framework
////////////////////////////////////////////////////////////////////////////////
class Framework
{
public:
	Framework();
	~Framework();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_Input = NULL;
	Renderer* m_Graphics = NULL;
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static Framework* ApplicationHandle = 0;


#endif