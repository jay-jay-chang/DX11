////////////////////////////////////////////////////////////////////////////////
// Filename: Shader.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Shader.h"

bool PolygonLayout::Setup_Layout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layoutDescList, int length, ShaderBuffer& buffer)
{
	HRESULT result = device->CreateInputLayout(layoutDescList, length, buffer.vertexShaderBuffer->GetBufferPointer(), buffer.vertexShaderBuffer->GetBufferSize(),
		&m_layout);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void PolygonLayout::Release()
{
	if (m_layout)
	{
		m_layout->Release();
	}
}

void PolygonLayout::SetPosition(D3D11_INPUT_ELEMENT_DESC& polygonLayout, UINT alignOffset)
{
	polygonLayout.SemanticName = "POSITION";
	polygonLayout.SemanticIndex = 0;
	polygonLayout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout.InputSlot = 0;
	polygonLayout.AlignedByteOffset = alignOffset;
	polygonLayout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout.InstanceDataStepRate = 0;
}

void PolygonLayout::SetTexture(D3D11_INPUT_ELEMENT_DESC& polygonLayout, UINT alignOffset)
{
	polygonLayout.SemanticName = "TEXCOORD";
	polygonLayout.SemanticIndex = 0;
	polygonLayout.Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout.InputSlot = 0;
	polygonLayout.AlignedByteOffset = alignOffset;
	polygonLayout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout.InstanceDataStepRate = 0;
}

void PolygonLayout::SetNormal(D3D11_INPUT_ELEMENT_DESC& polygonLayout, UINT alignOffset)
{
	polygonLayout.SemanticName = "NORMAL";
	polygonLayout.SemanticIndex = 0;
	polygonLayout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout.InputSlot = 0;
	polygonLayout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout.InstanceDataStepRate = 0;

}

bool BufferObject::Setup_matrix(ID3D11Device* device)
{
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	HRESULT result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_buffer);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

bool BufferObject::Setup_light(ID3D11Device* device)
{
	D3D11_BUFFER_DESC lightBufferDesc;
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	HRESULT result = device->CreateBuffer(&lightBufferDesc, NULL, &m_buffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool BufferObject::Setup_camera(ID3D11Device* device)
{
	D3D11_BUFFER_DESC cameraBufferDesc;
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;

	// Create the camera constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	HRESULT result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_buffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void BufferObject::Release()
{
	if (m_buffer)
	{
		m_buffer->Release();
	}
}

bool TextureSampler::Setup_defult(ID3D11Device* device)
{
	// Create a texture sampler state description.
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	HRESULT result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void TextureSampler::Release()
{
	if (m_sampleState)
	{
		m_sampleState->Release();
	}
}

bool ShaderDesc_Texture::Setup(ID3D11Device* device, ShaderBuffer& buffer)
{
	D3D11_INPUT_ELEMENT_DESC layoutDesc[2];
	layout.SetPosition(layoutDesc[0], 0);
	layout.SetTexture(layoutDesc[1], D3D11_APPEND_ALIGNED_ELEMENT);
	if (!layout.Setup_Layout(device, &layoutDesc[0], layoutLen, buffer))
	{
		return false;
	}
	if (!matrixBuffer.Setup_matrix(device))
	{
		return false;
	}
	if (!sampler.Setup_defult(device))
	{
		return false;
	}
	return true;
}

void ShaderDesc_Texture::Release()
{
	layout.Release();
	matrixBuffer.Release();
	sampler.Release();
}

bool ShaderDesc_TexLight::Setup(ID3D11Device* device, ShaderBuffer& buffer)
{
	D3D11_INPUT_ELEMENT_DESC layoutDesc[3];
	layout.SetPosition(layoutDesc[0], 0);
	layout.SetTexture(layoutDesc[1], D3D11_APPEND_ALIGNED_ELEMENT);
	layout.SetNormal(layoutDesc[2], D3D11_APPEND_ALIGNED_ELEMENT);
	if (!layout.Setup_Layout(device, &layoutDesc[0], layoutLen, buffer))
	{
		return false;
	}
	if (!matrixBuffer.Setup_matrix(device))
	{
		return false;
	}
	if (!lightBuffer.Setup_matrix(device))
	{
		return false;
	}
	if (!cameraBuffer.Setup_camera(device))
	{
		return false;
	}
	if (!sampler.Setup_defult(device))
	{
		return false;
	}
	return true;
}

void ShaderDesc_TexLight::Release()
{
	layout.Release();
	matrixBuffer.Release();
	sampler.Release();
	lightBuffer.Release();
	cameraBuffer.Release();
}

Shader::Shader(TYPE type)
{
	m_type = type;
}


Shader::~Shader()
{
}


bool Shader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Initialize the vertex and pixel shaders.
	if (m_type == TYPE::TEXTURE)
	{
		m_desc = new ShaderDesc_Texture();
		result = InitializeShader(device, hwnd, L"shader/texture.vs", L"shader/texture.ps");
	}
	else if (m_type == TYPE::DIFFUSE)
	{
		m_desc = new ShaderDesc_TexLight();
		result = InitializeShader(device, hwnd, L"shader/light.vs", L"shader/light.ps");
	}
	if(!result)
	{
		return false;
	}

	return true;
}


void Shader::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}
bool Shader::Render(ID3D11DeviceContext* deviceContext, ShaderParameter& param)
{
	switch (m_type)
	{
	case Shader::TEXTURE:
		return Render(deviceContext, param, (ShaderDesc_Texture*)m_desc);
	case Shader::DIFFUSE:
		return Render(deviceContext, param, (ShaderDesc_TexLight*)m_desc);
	default:
		break;
	}
	//type error
	return false;
}

bool Shader::Render(ID3D11DeviceContext* deviceContext, ShaderParameter& param, ShaderDesc_Texture* desc)
{
	bool result;
	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, param, desc);
	if(!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, param, desc);

	return true;
}

bool Shader::Render(ID3D11DeviceContext* deviceContext, ShaderParameter& param, ShaderDesc_TexLight* desc)
{
	bool result;
	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, param, desc);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, param, desc);

	return true;
}

bool Shader::compileShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename, ShaderBuffer& buffer)
{
	HRESULT result;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	// Compile the vertex shader code.
	result = D3DCompileFromFile(vsFilename, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, "DXVertexShader", "vs_4_0", flags, 0,
		&buffer.vertexShaderBuffer, &buffer.errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (buffer.errorMessage)
		{
			OutputShaderErrorMessage(buffer.errorMessage, hwnd, vsFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Compile the pixel shader code.
	result = D3DCompileFromFile(psFilename, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, "DXPixelShader", "ps_4_0", flags, 0,
		&buffer.pixelShaderBuffer, &buffer.errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (buffer.errorMessage)
		{
			OutputShaderErrorMessage(buffer.errorMessage, hwnd, psFilename);
		}
		// If there was  nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(buffer.vertexShaderBuffer->GetBufferPointer(), buffer.vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(buffer.pixelShaderBuffer->GetBufferPointer(), buffer.pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

bool Shader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{;
	ShaderBuffer buffer;

	//Compile shader and create buffer
	if (!compileShader(device, hwnd, vsFilename, psFilename, buffer))
	{
		return false;
	}

	if(!m_desc->Setup(device, buffer))
	//if (!setupShaderDesc(device, desc, buffer))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	buffer.vertexShaderBuffer->Release();
	buffer.pixelShaderBuffer->Release();

	return true;
}


void Shader::ShutdownShader()
{
	// Release shader descript.
	if (m_desc)
	{
		m_desc->Release();
		delete m_desc;
		m_desc = NULL;
	}

	// Release the pixel shader.
	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = NULL;
	}

	// Release the vertex shader.
	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = NULL;
	}

	return;
}


void Shader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = NULL;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}


bool Shader::SetShaderParameters(ID3D11DeviceContext* deviceContext, ShaderParameter& param, ShaderDesc_Texture* desc)
{
	HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
	BufferObject::MatrixBufferType* dataPtr;
	unsigned int bufferNumber;


	// Transpose the matrices to prepare them for the shader.
	XMMATRIX worldMatrix = XMMatrixTranspose(param.worldMatrix);
	XMMATRIX viewMatrix = XMMatrixTranspose(param.viewMatrix);
	XMMATRIX projectionMatrix = XMMatrixTranspose(param.projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(desc->matrixBuffer.m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (BufferObject::MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
    deviceContext->Unmap(desc->matrixBuffer.m_buffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &desc->matrixBuffer.m_buffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &param.texture);

	return true;
}

bool Shader::SetShaderParameters(ID3D11DeviceContext* deviceContext, ShaderParameter& param, ShaderDesc_TexLight* desc)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	BufferObject::MatrixBufferType* dataPtr;
	BufferObject::LightBufferType* dataPtr2;
	BufferObject::CameraBufferType* dataPtr3;


	unsigned int bufferNumber;
	static float angle = 0.0f;
	angle += 0.01f;
	if (angle > 2.0f)
	{
		angle = 0.0f;
	}
	param.worldMatrix = XMMatrixRotationY(3.14f*angle);
	// Transpose the matrices to prepare them for the shader.
	XMMATRIX worldMatrix = XMMatrixTranspose(param.worldMatrix);
	XMMATRIX viewMatrix = XMMatrixTranspose(param.viewMatrix);
	XMMATRIX projectionMatrix = XMMatrixTranspose(param.projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(desc->matrixBuffer.m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (BufferObject::MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(desc->matrixBuffer.m_buffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &desc->matrixBuffer.m_buffer);

	// we lock the camera buffer and set the camera position value in it.

		// Lock the camera constant buffer so it can be written to.
	result = deviceContext->Map(desc->cameraBuffer.m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr3 = (BufferObject::CameraBufferType*)mappedResource.pData;

	// Copy the camera position into the constant buffer.
	dataPtr3->cameraPosition = param.vec3_2;
	dataPtr3->padding = 0.0f;

	// Unlock the camera constant buffer.
	deviceContext->Unmap(desc->cameraBuffer.m_buffer, 0);

	// Note that we set the bufferNumber to 1 instead of 0 before setting the constant buffer.
	// This is because it is the second buffer in the vertex shader(the first being the matrix buffer).
	// Set the position of the camera constant buffer in the vertex shader.
	bufferNumber = 1;

	// Now set the camera constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &desc->cameraBuffer.m_buffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &param.texture);

	// Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(desc->lightBuffer.m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the light constant buffer.
	dataPtr2 = (BufferObject::LightBufferType*)mappedResource.pData;

	// The light constant buffer now sets the specular color and specular power so that the pixel shader can perform specular lighting calculations.
	// Copy the lighting variables into the light constant buffer.
	dataPtr2->ambientColor = param.vec4_2;
	dataPtr2->diffuseColor = param.vec4_1;
	dataPtr2->lightDirection = param.vec3_1;
	dataPtr2->specularColor = param.vec4_3;
	dataPtr2->specularPower = param.f_1;

	// Unlock the light constant buffer.
	deviceContext->Unmap(desc->lightBuffer.m_buffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &desc->lightBuffer.m_buffer);

	return true;
}

void Shader::RenderShader(ID3D11DeviceContext* deviceContext, ShaderParameter& param, ShaderDesc_Texture* desc)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(desc->layout.m_layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &desc->sampler.m_sampleState);

	// Render the triangle.
	deviceContext->DrawIndexed(param.indexCount, 0, 0);

	return;
}

void Shader::RenderShader(ID3D11DeviceContext* deviceContext, ShaderParameter& param, ShaderDesc_TexLight* desc)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(desc->layout.m_layout);

    // Set the vertex and pixel shaders that will be used to render this triangle.
    deviceContext->VSSetShader(m_vertexShader, NULL, 0);
    deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &desc->sampler.m_sampleState);

	// Render the triangle.
	deviceContext->DrawIndexed(param.indexCount, 0, 0);

	return;
}