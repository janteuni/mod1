#include "../include/Camera.hpp"

/* ----------------- Constructor ---------------------*/

Camera::Camera()
{
	this->_position = vec3(0.0, 0.0, 0.0);
}

Camera::~Camera(void)
{
}

Camera::Camera(Camera const & ref)
{
	*this = ref;
}

Camera & Camera::operator=(Camera const & ref)
{
	this->_projectionMatrix  = ref.GetProjectionMatrix();
	this->_position = ref.GetPosition();
	this->_speed = ref.GetSpeed();
	this->_yaw = ref.GetYaw();
	this->_pitch = ref.GetPitch();
	return *this;
}

mat4 Camera::GetProjectionMatrix(void) const
{
	return this->_projectionMatrix;
}

vec3 Camera::GetPosition(void) const
{
	return this->_position;
}

float Camera::GetYaw(void) const
{
	return this->_yaw;
}

float Camera::GetPitch(void) const
{
	return this->_pitch;
}

double Camera::GetSpeed(void) const
{
	return this->_speed;
}

void Camera::SetYaw(float yaw)
{
	this->_yaw = yaw;
}

void Camera::SetPitch(float pitch)
{
	this->_pitch = pitch;
}

void Camera::SetSpeed(double speed)
{
	this->_speed = speed;
}

void Camera::SetPosition(vec3 position)
{
	this->_position = position;
}

void Camera::SetRotationSpeed(double speed)
{
	this->_rotationSpeed = speed;
}

double Camera::GetRotationSpeed(void)
{
	return this->_rotationSpeed;
}


/* ----------------- Main Function ---------------------*/

mat4 Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	this->_projectionMatrix = perspective(fov, aspectRatio, nearPlane, farPlane);
	return this->_projectionMatrix;
}


void Camera::PositionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch)
{
	this->_position = vec3( positionX, positionY, positionZ );
	this->_yaw = yaw;
	this->_pitch = pitch;
}

mat4 Camera::GetRotationMatrix()
{
	mat4 rotationMatrix(1.0f);

	rotationMatrix = rotate(rotationMatrix, this->_pitch, vec3(1, 0, 0));
	rotationMatrix = rotate(rotationMatrix, this->_yaw, vec3(0, 1, 0));
	return rotationMatrix;
}


mat4 Camera::GetViewMatrix()
{
	return GetRotationMatrix() * inverse(translate(mat4(), this->_position));
}


vec3 Camera::GetView()
{
	vec4 viewVector = inverse(GetRotationMatrix()) * vec4(0, 0, -1, 1);
	return vec3(viewVector);
}


vec3 Camera::GetUp()
{
	vec4 upVector = inverse(GetRotationMatrix()) * vec4(0, 1, 0, 1);
	return vec3(upVector);
}

vec3 Camera::GetRight(void)
{
	vec4 rightVector = inverse(GetRotationMatrix()) * vec4(1, 0, 0, 1);
	return vec3(rightVector);
}

void Camera::Strafe(float speed)
{
	vec3 rightVector = GetRight();

	this->_position.x += rightVector.x * speed;
	this->_position.z += rightVector.z * speed;
}


void Camera::SetViewByMouse(float xOffset, float yOffset)
{
	this->_yaw += xOffset * this->_mouseSpeed;
	this->_pitch += yOffset * this->_mouseSpeed;

	if (this->_yaw > 2 * PI) {
		this->_yaw = 0;
	}

	if (this->_yaw < 0) {
		this->_yaw = 2 * PI;
	}

	if (this->_pitch > radians(75.0f)) {
		this->_pitch = radians(75.0f);
	}
	if (this->_pitch < radians(-75.0f)) {
		this->_pitch = radians(-75.0f);
	}
}

void Camera::MoveCamera(float speed)
{
	vec3 viewVector = GetView();
	this->_position.x += viewVector.x * speed;
	this->_position.z += viewVector.z * speed;
}
