#include "../include/Camera.hpp"

/* ----------------- Constructor ---------------------*/

Camera::Camera()
{
	this->_position = glm::vec3(0.0, 0.0, 0.0);
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

glm::mat4 Camera::GetProjectionMatrix(void) const
{
	return this->_projectionMatrix;
}

glm::vec3 Camera::GetPosition(void) const
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

void Camera::SetPosition(glm::vec3 position)
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

glm::mat4 Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	this->_projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	return this->_projectionMatrix;
}


void Camera::PositionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch)
{
	this->_position = glm::vec3( positionX, positionY, positionZ );
	this->_yaw = yaw;
	this->_pitch = pitch;
}

glm::mat4 Camera::GetRotationMatrix()
{
	glm::mat4 rotationMatrix(1.0f);

	rotationMatrix = rotate(rotationMatrix, this->_pitch, glm::vec3(1, 0, 0));
	rotationMatrix = rotate(rotationMatrix, this->_yaw, glm::vec3(0, 1, 0));
	return rotationMatrix;
}


glm::mat4 Camera::GetViewMatrix()
{
	return GetRotationMatrix() * inverse(translate(glm::mat4(), this->_position));
}


glm::vec3 Camera::GetView()
{
	glm::vec4 viewVector = inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(viewVector);
}


glm::vec3 Camera::GetUp()
{
	glm::vec4 upVector = inverse(GetRotationMatrix()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(upVector);
}

glm::vec3 Camera::GetRight(void)
{
	glm::vec4 rightVector = inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(rightVector);
}

void Camera::Strafe(float speed)
{
	glm::vec3 rightVector = GetRight();

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

	if (this->_pitch > glm::radians(75.0f)) {
		this->_pitch = glm::radians(75.0f);
	}
	if (this->_pitch < glm::radians(-75.0f)) {
		this->_pitch = glm::radians(-75.0f);
	}
}

void Camera::MoveCamera(float speed)
{
	glm::vec3 viewVector = GetView();
	this->_position.x += viewVector.x * speed;
	this->_position.y += viewVector.y * speed;
	this->_position.z += viewVector.z * speed;
//	std::cout << this->_position.x << " " << this->_position.y << " " << this->_position.z << " " << this->_pitch << " " << this->_yaw << std::endl;
}
