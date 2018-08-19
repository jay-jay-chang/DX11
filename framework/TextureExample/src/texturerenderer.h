////////////////////////////////////////////////////////////////////////////////
// Filename: TextureRenderer.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TextureRenderer_H_
#define _TextureRenderer_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "renderdevice.h"
#include "camera.h"
#include "texturemodel.h"
#include "textureshader.h"


/////////////
// GLOBALS //
/////////////
//const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: Renderer
////////////////////////////////////////////////////////////////////////////////
class TextureRenderer
{
public:
	TextureRenderer();
	TextureRenderer(const TextureRenderer&);
	~TextureRenderer();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	RenderDevice* m_D3D = NULL;
	Camera* m_Camera = NULL;
	Texture* m_texture = NULL;
	TextureModel* m_Model = NULL;
	TextureShader* m_textureShader = NULL;
};

#endif