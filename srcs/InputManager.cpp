#include "../include/InputManager.hpp"
#include "../include/TimeManager.hpp"

InputManager::InputManager(void)
{
}

InputManager::~InputManager(void)
{
}

void InputManager::SetCamera(Camera * ptr)
{
	this->_camera = ptr;
}

Camera * InputManager::GetCamera(void) const
{
	return this->_camera;
}

void InputManager::KeyPressed(InputCodes code)
{
	if (this->_camera == nullptr) {
		return ;
	}

	if (code == Up) {
		this->_camera->MoveCamera(this->_camera->GetSpeed() * TimeManager::Instance().DeltaTime);
	}
	else if (code == Down) {
		this->_camera->MoveCamera(-1 * this->_camera->GetSpeed() * TimeManager::Instance().DeltaTime);
	}
	else if (code == Left) {
		this->_camera->Strafe(-1 * this->_camera->GetSpeed() * TimeManager::Instance().DeltaTime);
	}
	else if (code == Right) {
		this->_camera->Strafe(this->_camera->GetSpeed() * TimeManager::Instance().DeltaTime);
	}
}

void InputManager::MouseMoved(float mouseX, float mouseY)
{
	if (this->_camera == nullptr) {
		return;
	}
	this->_camera->SetViewByMouse(mouseX, mouseY);
}
