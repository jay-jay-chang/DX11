////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Model_H_
#define _Model_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "texture.h"

using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class Model
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};


public:
	Model();
	~Model();

	bool Initialize(ID3D11Device*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	void SetTexture(Texture*);

	void GetWorldMatrix(XMMATRIX&);
	void SetPosition(XMFLOAT3 pos);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadModel(char*);

	void ReleaseModel();
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer = NULL, *m_indexBuffer = NULL;
	int m_vertexCount, m_indexCount;
	Texture* m_Texture = NULL;
	ModelType* m_model = NULL;
	XMFLOAT4X4 m_worldMatrix;
};

#endif