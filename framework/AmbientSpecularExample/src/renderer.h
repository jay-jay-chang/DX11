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
#include "shader.h"
#include "light.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
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
	Texture* m_texture = NULL;
	Model* m_Model = NULL;
	Shader* m_Shader = NULL;
	Light* m_light = NULL;
};

#endif