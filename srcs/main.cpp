#include "GL/glew.h"
#include "../include/Window.hpp"
#include "../include/Application.hpp"
#include "../include/Camera.hpp"

int			main(void)
{
	Window * 		window = new Window();
	Camera * 		camera = new Camera();
	Application 	application;

	application.SetWindowManager(window);
	application.SetCamera(camera);
	window->GetInputManager()->SetCamera(camera);

	return application.GLMain();
}
