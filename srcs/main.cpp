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
	std::ifstream	fs;
	int				i;

	if (argc == 3) {
		file = argv[2];
	} else {
		file = "demo1.mod1";
	}

	//check file extension
	if ( file.length() < 5 || file.substr(file.length() - 5) != ".mod1") {
		std::cout << "Error : file extension not valid" << std::endl;
		return -1;
	}

	//check file opens
	fs.open(file.c_str());
	if (fs) {
		if (argc > 1) {
			i = atoi(argv[1]);
			if (i >= 1 && i <= 5) {
				application.setScenario(i);
			}
		}
		application.SetWindowManager(window);
		application.SetCamera(camera);
		window->GetInputManager()->SetCamera(camera);
		return application.GLMain(fs);
	}
	std::cout << "Error : failed to open file [" << file << "]" << std::endl;
	return -1;
}
