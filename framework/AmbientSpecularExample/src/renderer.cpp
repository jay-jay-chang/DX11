////////////////////////////////////////////////////////////////////////////////
// Filename: Renderer.cpp
////////////////////////////////////////////////////////////////////////////////
#include "renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


bool Renderer::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new RenderDevice;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	//Create texture
	m_texture = new Texture;
	result = m_texture->Initialize(m_D3D->GetDevice(), L"data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Texture not found", L"Error", MB_OK);
		return false;
	}
	
	// Create the model object.
	m_Model = new Model;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "data/cube.txt");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_Model->SetTexture(m_texture);

	// Create the texture shader object.
	m_Shader = new Shader(Shader::TYPE::DIFFUSE);
	if(!m_Shader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_Shader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_light = new Light;

	// Initialize the light object.
	m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetDirection(0.0f, 0.0f, 1.0f);
	m_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetSpecularPower(32.0f);

	return true;
}


void Renderer::Shutdown()
{
	// Release the light object.
	if (m_light)
	{
		delete m_light;
		m_light = NULL;
	}

	// Release the texture object.
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}

	//Release the shader object
	if(m_Shader)
	{
		m_Shader->Shutdown();
		delete m_Shader;
		m_Shader = NULL;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = NULL;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = NULL;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = NULL;
	}

	return;
}


bool Renderer::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool Renderer::Render()
{
	bool result;
	ShaderParameter param;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(param.viewMatrix);
	m_Model->GetWorldMatrix(param.worldMatrix);
	m_D3D->GetProjectionMatrix(param.projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	param.indexCount = m_Model->GetIndexCount();
	param.texture = m_Model->GetTexture();
	param.vec4_1 = m_light->GetDiffuseColor();
	param.vec4_2 = m_light->GetAmbientColor();
	param.vec4_3 = m_light->GetSpecularColor();
	param.vec3_1 = m_light->GetDirection();
	param.vec3_2 = m_Camera->GetPosition();
	param.f_1 = m_light->GetSpecularPower();


	// Render the model using the color shader.
	result = m_Shader->Render(m_D3D->GetDeviceContext(), param);
	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}