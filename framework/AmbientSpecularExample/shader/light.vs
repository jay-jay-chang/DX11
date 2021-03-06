////////////////////////////////////////////////////////////////////////////////
// Filename: light.vs
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
}
	
//We add a new constant buffer to hold camera information.
//In this shader we require the position of the camera to determine where this vertex is being viewed from for specular calculations.
cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

//The PixelInputType structure is modified as the viewing direction needs to be calculated in the vertex shader and then sent into the pixel shader for specular lighting calculations.
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : POSITION;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType DXVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;


    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);
	
	// The viewing direction is calculated here in the vertex shader.
	// We calculate the world position of the vertex and subtract that from the camera position to determine where we are viewing the scene from.
	// The final value is normalized and sent into the pixel shader.
    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	
    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);

    return output;

}