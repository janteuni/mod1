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
	this->_cube = new Cube();
	this->_water = new Water();
	this->_camera->SetPerspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	this->_camera->PositionCamera(-35.8552, 21.4029, 9.61716, 1.823 ,0.0610029);
	this->_landscape->SetCamera(this->_camera);
	this->_cube->SetCamera(this->_camera);
	this->_landscape->SetPosition(vec3(0, 0, 0));
	this->_cube->SetPosition(vec3(0, 0, 0));
}

void Application::GameLoop(void)
{
	int loop = 0;

	while (this->_WM->ProcessInput(true)) {
		TimeManager::Instance().CalculateFrameRate(false);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the landscape
		this->_landscape->Render();

		// if scenario = rise of water => increase water
		if (loop < 500) {
			this->_water->addWater(0, 0, 1);
			this->_water->addWater(0, 1, 1);
			this->_water->addWater(0, 49, 1);
			this->_water->addWater(0, 48, 1);
			this->_water->addWater(49, 0, 1);
			this->_water->addWater(49, 1, 1);
			this->_water->addWater(49, 48, 1);
			this->_water->addWater(49, 49, 1);
		}

		// Render the water
		for (int x = 0; x < 50; x++) {
			for(int z = 0; z < 50; z++) {
				this->_water->averageZone(x, z, this->_landscape->getMap());
				float land = this->_landscape->getMap()[x][z];
				float water = this->_water->getMapWater()[x][z];
				if (water > 0.000000f) {
					this->_cube->SetScale(vec3(1.0f, water, 1.0f));
					this->_cube->SetPosition(vec3(x, land, z));
					this->_cube->Render();
				}
			}
		}

		loop++;
		// Swap buffer to view it on the screen
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
	if (this->_cube) {
		delete this->_cube;
		this->_cube = nullptr;
	}
	if (this->_water) {
		delete this->_water;
		this->_water = nullptr;
	}
}
