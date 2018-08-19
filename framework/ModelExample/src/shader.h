////////////////////////////////////////////////////////////////////////////////
// Filename: Shader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Shader_H_
#define _Shader_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <fstream>
using namespace std;
using namespace DirectX;

struct ShaderBuffer
{
	ID3D10Blob* vertexShaderBuffer = NULL;
	ID3D10Blob* pixelShaderBuffer = NULL;
	ID3D10Blob* errorMessage = NULL;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: PolygonLayout
////////////////////////////////////////////////////////////////////////////////
class PolygonLayout
{
public:
	bool Setup_Layout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layoutDescList, int length, ShaderBuffer& buffer);
	void Release();
	void SetPosition(D3D11_INPUT_ELEMENT_DESC& desc, UINT alignOffset);
	void SetTexture(D3D11_INPUT_ELEMENT_DESC& desc, UINT alignOffset);
	void SetNormal(D3D11_INPUT_ELEMENT_DESC& desc, UINT alignOffset);
	ID3D11InputLayout* m_layout = NULL;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: BufferObject
////////////////////////////////////////////////////////////////////////////////
class BufferObject
{
public:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

	bool Setup_matrix(ID3D11Device*);
	bool Setup_light(ID3D11Device*);
	void Release();

	ID3D11Buffer * m_buffer = NULL;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureSampler
////////////////////////////////////////////////////////////////////////////////
class TextureSampler
{
public:
	bool Setup_defult(ID3D11Device*);
	void Release();

	ID3D11SamplerState* m_sampleState = NULL;
};

////////////////////////////////////////////////////////////////////////////////
//Class name: ShaderParameter
////////////////////////////////////////////////////////////////////////////////
class ShaderParameter
{
public:
	int indexCount;
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
	ID3D11ShaderResourceView* texture = NULL;
	XMFLOAT3 vec3_1;
	XMFLOAT4 vec4_1;
};

////////////////////////////////////////////////////////////////////////////////
//Class name: ShaderDesc
////////////////////////////////////////////////////////////////////////////////
class ShaderDesc
{
public:
	ShaderDesc() {}
	virtual ~ShaderDesc() {}
	virtual bool Setup(ID3D11Device* device, ShaderBuffer& buffer) = 0;
	virtual void Release() = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderDesc_Texture
////////////////////////////////////////////////////////////////////////////////
class ShaderDesc_Texture : public ShaderDesc
{
public:
	PolygonLayout layout;
	unsigned int layoutLen = 2;
	BufferObject matrixBuffer;
	TextureSampler sampler;

	ShaderDesc_Texture() {}
	virtual ~ShaderDesc_Texture() {}
	bool Setup(ID3D11Device* device, ShaderBuffer& buffer);
	void Release();
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderDesc_TexDiffuse
////////////////////////////////////////////////////////////////////////////////
class ShaderDesc_TexDiffuse : public ShaderDesc
{
public:
	PolygonLayout layout;
	unsigned int layoutLen = 3;
	BufferObject matrixBuffer;
	BufferObject lightBuffer;
	TextureSampler sampler;

	ShaderDesc_TexDiffuse() {}
	virtual ~ShaderDesc_TexDiffuse() {}
	bool Setup(ID3D11Device* device, ShaderBuffer& buffer);
	void Release();
};

////////////////////////////////////////////////////////////////////////////////
// Class name: Shader
////////////////////////////////////////////////////////////////////////////////
class Shader
{
public :
	enum TYPE
	{
		TEXTURE = 0,
		DIFFUSE = 1,
	};

private:

public:
	Shader(TYPE type);
	~Shader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, ShaderParameter& param);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, ShaderParameter& param, ShaderDesc_Texture*);
	bool SetShaderParameters(ID3D11DeviceContext*, ShaderParameter& param, ShaderDesc_TexDiffuse*);
	void RenderShader(ID3D11DeviceContext*, ShaderParameter& param, ShaderDesc_Texture*);
	void RenderShader(ID3D11DeviceContext*, ShaderParameter& param, ShaderDesc_TexDiffuse*);
	bool Render(ID3D11DeviceContext*, ShaderParameter& param, ShaderDesc_Texture*);
	bool Render(ID3D11DeviceContext*, ShaderParameter& param, ShaderDesc_TexDiffuse*);

	bool compileShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename, ShaderBuffer& buffer);
	bool setupShaderDesc(ID3D11Device* device, ShaderDesc_Texture& desc, ShaderBuffer& buffer);

private:
	ID3D11VertexShader* m_vertexShader = NULL;
	ID3D11PixelShader* m_pixelShader = NULL;
	ShaderDesc* m_desc = NULL;

private:
	TYPE m_type = TYPE::TEXTURE;
};

#endif