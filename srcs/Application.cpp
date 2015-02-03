#include "GL/glew.h"
#include "../include/Application.hpp"
Model g_Model;

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

int Application::GLMain(void)
{
	this->Initialize();
	this->GameLoop();
	this->Destroy();

	return 0;
}


void Application::Initialize(void)
{
	if (!this->_WM || this->_WM->Initialize(1024, 768, "Awesome Mod 1", false) != 0) {
		exit(-1);
	}

	glViewport(0, 0, this->ScreenWidth, this->ScreenHeight);
	glEnable(GL_DEPTH_TEST);

	Vertex3 vertices[120];

	for (float i = 0; i < 120; i += 6)
	{
		vertices[0 + (int)i].xyz = vec3(-5.0f + i / 10, -5.0f + i, -5.0f + i / 10);
		vertices[0 + (int)i].rgba = vec4(1, 1, 0, 1);

		vertices[1 + (int)i].xyz = vec3(5.0f - i / 10, -5.0f + i, -5.0f + i / 10);
		vertices[1 + (int)i].rgba = vec4(1, 0, 0, 1);

		vertices[2 + (int)i].xyz = vec3(5.0f - i / 10, -5.0f + i, 5.0f - i / 10);
		vertices[2 + (int)i].rgba = vec4(0, 1, 1, 1);

		vertices[3 + (int)i].xyz = vec3(5.0f - i / 10, -5.0f + i, 5.0f - i / 10);
		vertices[3 + (int)i].rgba = vec4(0, 1, 1, 1);

		vertices[4 + (int)i].xyz = vec3(-5.0f + i / 10, -5.0f + i, 5.0f - i / 10);
		vertices[4 + (int)i].rgba = vec4(0, 0, 1, 1);

		vertices[5 + (int)i].xyz = vec3(-5.0f + i / 10, -5.0f + i, -5.0f + i / 10);
		vertices[5 + (int)i].rgba = vec4(1, 1, 0, 1);
	}

	g_Model.Initialize(vertices, 120, "Shaders/Shader.vertex", "Shaders/Shader.fragment");
	this->_camera->SetPerspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	this->_camera->PositionCamera(0, 0, 6,		0,		0);
	g_Model.SetCamera(this->_camera);
	g_Model.SetPosition(vec3(0, 0, 0));
}


void Application::GameLoop(void)
{
	while (this->_WM->ProcessInput(true)) {
		TimeManager::Instance().CalculateFrameRate(false);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		g_Model.Render();
		this->_WM->SwapTheBuffers();
	}
}


void Application::Destroy()
{
	g_Model.Destroy();
	if (this->_WM) {
		this->_WM->Destroy();

		delete this->_WM;
		this->_WM = nullptr;
	}
	if (this->_camera) {
		delete this->_camera;
		this->_camera = nullptr;
	}
}
