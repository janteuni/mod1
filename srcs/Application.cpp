#include "GL/glew.h"
#include "../include/Application.hpp"

/* -------------------------- CONSTRUCTOR --------------------------- */

Application::Application(void)
{
}

Application::~Application(void)
{
	this->Destroy();
}

Application & Application::operator=(Application const & ref)
{
	this->_WM = ref.GetWindowManager();
	return *this;
}

WindowManager * Application::GetWindowManager(void) const
{
	return this->_WM;
}

void Application::SetWindowManager(WindowManager * ptrWM)
{
   this->_WM = ptrWM;
}

Camera * Application::GetCamera(void) const
{
	return this->_camera;
}

void Application::SetCamera(Camera * ptr)
{
	this->_camera = ptr;
}

/* --------------------------- MAIN FUNCTION ---------------------------- */

int Application::GLMain(std::string file)
{
	this->Initialize(file);
	this->GameLoop();
	this->_landscape = new Landscape(file);
	return 0;
}


void Application::Initialize(std::string file)
{
	if (!this->_WM || this->_WM->Initialize(this->ScreenWidth, this->ScreenHeight, "Awesome Mod 1", false) != 0) {
		exit(-1);
	}
	glViewport(0, 0, this->ScreenWidth, this->ScreenHeight);
	glEnable(GL_DEPTH_TEST);

	this->_landscape = new Landscape(file);
	this->_camera->SetPerspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	this->_camera->PositionCamera(-35.8552, 21.4029, 9.61716, 1.823 ,0.0610029);
	this->_landscape->SetCamera(this->_camera);
	this->_landscape->SetPosition(vec3(0, 0, 0));
}


void Application::GameLoop(void)
{
	while (this->_WM->ProcessInput(true)) {
		TimeManager::Instance().CalculateFrameRate(false);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->_landscape->Render();
		this->_WM->SwapTheBuffers();
	}
}


void Application::Destroy()
{
	if (this->_WM) {
		this->_WM->Destroy();
		delete this->_WM;
		this->_WM = nullptr;
	}
	if (this->_camera) {
		delete this->_camera;
		this->_camera = nullptr;
	}
	if (this->_landscape) {
		delete this->_landscape;
		this->_landscape = nullptr;
	}
}
