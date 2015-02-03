#include "GL/glew.h"
#include "../include/Window.hpp"
#include "../include/Application.hpp"
#include "../include/Camera.hpp"

int			main(int argc, char ** argv)
{
	Window * 		window = new Window();
	Camera * 		camera = new Camera();
	Application 	application;
	std::string		file;

	if (argc == 2) {
		file = argv[1];
	} else {
		file = "demo1.mod1";
	}
	application.SetWindowManager(window);
	application.SetCamera(camera);
	window->GetInputManager()->SetCamera(camera);
	return application.GLMain(file);
}
