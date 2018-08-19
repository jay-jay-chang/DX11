////////////////////////////////////////////////////////////////////////////////
// Filename: Camera.cpp
////////////////////////////////////////////////////////////////////////////////
#include "camera.h"

Camera::Camera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


Camera::~Camera()
{
}


void Camera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void Camera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


XMFLOAT4 Camera::GetPosition()
{
	return XMFLOAT4(m_positionX, m_positionY, m_positionZ, 1.0f);
}


void Camera::Update()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = { 0.0f, 1.0f, 0.0f, 0.0f };

	// Setup the position of the camera in the world.
	//position.x = m_positionX;
	//position.y = m_positionY;
	//position.z = m_positionZ;
	position = { m_positionX, m_positionY, m_positionZ, 1.0f };

	// Setup where the camera is looking by default.;
	lookAt = { 0.0f, 0.0f, 1.0f, 0.0f };

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	XMVECTOR quat = XMQuaternionRotationMatrix(rotationMatrix);
	lookAt = XMVector3Rotate(lookAt, quat);
	up = XMVector3Rotate(up, quat);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	XMStoreFloat4x4(&m_viewMatrix, XMMatrixLookAtLH(position, lookAt, up));

	return;
}


void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = XMLoadFloat4x4(&m_viewMatrix);
	return;
}