#include "../include/WindowManager.hpp"

WindowManager::WindowManager(void)
{
}

WindowManager::~WindowManager(void)
{
}

InputManager * WindowManager::GetInputManager(void)
{
	return &this->inputManager;
}
