#include "GL/glew.h"
#include "../include/Application.hpp"

/* -------------------------- CONSTRUCTOR --------------------------- */

Application::Application(void): _scenario(1)
{
}

Application::~Application(void)
{
	this->Destroy();
}

Application & Application::operator=(Application const & ref)
{
	this->_WM = ref.GetWindowManager();
	this->_camera = ref.GetCamera();
	this->_landscape = ref.getLandscape();
	this->_water = ref.getWater();
	this->_cube = ref.getCube();
	this->_scenario = ref.getScenario();
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

void Application::setScenario(int scenario)
{
	this->_scenario = scenario;
}

int Application::getScenario(void) const
{
	return this->_scenario;
}

Landscape * Application::getLandscape(void) const
{
	return this->_landscape;
}

Water * Application::getWater(void) const
{
	return this->_water;
}

Cube * Application::getCube(void) const
{
	return this->_cube;
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
	this->_water = new Water(this->_scenario);
	this->_camera->SetPerspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	// set position of camera above the landscape
	this->_camera->PositionCamera(-41.4151, 45.483, 19.0202, 1.685, 0.420003);
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
		if ((this->_scenario == RISE || this->_scenario == EMPTY) && loop < 300) {
			this->_water->updateWater();
		}
		if (this->_scenario == EMPTY && loop > 350) {
			this->_water->removeWater();
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
