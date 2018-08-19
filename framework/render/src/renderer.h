////////////////////////////////////////////////////////////////////////////////
// Filename: Renderer.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Renderer_H_
#define _Renderer_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "renderdevice.h"
#include "camera.h"
#include "model.h"
#include "colorshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: Renderer
////////////////////////////////////////////////////////////////////////////////
class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	RenderDevice* m_D3D = NULL;
	Camera* m_Camera = NULL;
	Model* m_Model = NULL;
	ColorShaderClass* m_ColorShader = NULL;
};

#endif