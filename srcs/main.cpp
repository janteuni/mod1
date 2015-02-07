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
	int				i;

	if (argc == 3) {
		file = argv[2];
	} else {
		file = "demo1.mod1";
	}
	i = atoi(argv[1]);
	if (i >= 1 || i <= 3) {
		application.setScenario(i);
	}
	application.SetWindowManager(window);
	application.SetCamera(camera);
	window->GetInputManager()->SetCamera(camera);
	return application.GLMain(file);
}
