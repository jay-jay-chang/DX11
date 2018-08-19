////////////////////////////////////////////////////////////////////////////////
// Filename: RenderDevice.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderDevice_H_
#define _RenderDevice_H_


//////////////
// INCLUDES //
//////////////
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: RenderDevice
////////////////////////////////////////////////////////////////////////////////
class RenderDevice
{
public:
	RenderDevice();
	~RenderDevice();

	bool Initialize(int, int, bool, HWND, float, float);
	void Shutdown();
	
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

private:
	bool m_vsync_enabled = false;
	//dx11_0
	ID3D11Device* m_device = NULL;
	ID3D11DeviceContext* m_deviceContext = NULL;
	IDXGISwapChain* m_swapChain = NULL;
	//dx11_1 feature
	ID3D11Device1* m_device1 = NULL;
	ID3D11DeviceContext1*   m_deviceContext1 = NULL;
	IDXGISwapChain1* m_swapChain1 = NULL;

	ID3D11RenderTargetView* m_renderTargetView = NULL;
	ID3D11Texture2D* m_depthStencilBuffer = NULL;
	ID3D11DepthStencilState* m_depthStencilState = NULL;
	ID3D11DepthStencilView* m_depthStencilView = NULL;
	ID3D11RasterizerState* m_rasterState = NULL;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT4X4 m_orthoMatrix;
};

#endif