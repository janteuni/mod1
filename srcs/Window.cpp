#include "GL/glew.h"
#include "../include/Window.hpp"
#include "../include/Application.hpp"

Window::Window(void)
{
}

Window::~Window(void)
{
	this->Destroy();
}

Window & Window::operator=(Window const & ref)
{
	this->_window = ref.getWindow();
	return *this;
}

GLFWwindow * Window::getWindow(void) const
{
	return this->_window;
}

int Window::Initialize(int width, int height, std::string strTitle, bool bFullScreen)
{
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen) {
		this->_window = glfwCreateWindow(width, height, strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	} else {
		this->_window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr, nullptr);
	}
	if (this->_window == nullptr) {
		std::cout << "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3" << std::endl;
		this->Destroy();
		return -1;
	}

	glfwMakeContextCurrent(this->_window);
	glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(this->_window, 0, 0);
	glfwSwapInterval(0);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		std::cout << "Failed to initialize glew" << std::endl;
		return -1;
	}
	return 0;
}


void Window::SwapTheBuffers(void)
{
	glfwSwapBuffers(this->_window);
}


bool Window::ProcessInput(bool continueGame = true)
{
	if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->_window) != 0) {
		return false;
	}
	if (glfwGetKey(this->_window, GLFW_KEY_UP) || glfwGetKey(this->_window, GLFW_KEY_W)) {
		this->inputManager.KeyPressed(InputCodes::Up);
	}
	if (glfwGetKey(this->_window, GLFW_KEY_DOWN) || glfwGetKey(this->_window, GLFW_KEY_S)) {
		this->inputManager.KeyPressed(InputCodes::Down);
	}
	if (glfwGetKey(this->_window, GLFW_KEY_LEFT) || glfwGetKey(this->_window, GLFW_KEY_A)) {
		this->inputManager.KeyPressed(InputCodes::Left);
	}
	if (glfwGetKey(this->_window, GLFW_KEY_RIGHT) || glfwGetKey(this->_window, GLFW_KEY_D)) {
		this->inputManager.KeyPressed(InputCodes::Right);
	}

	double mouseX, mouseY;
	glfwGetCursorPos(this->_window, &mouseX, &mouseY);
	if (mouseX != 0 && mouseY != 0) {
		this->inputManager.MouseMoved((float)mouseX, (float)mouseY);
	}
	glfwSetCursorPos(this->_window, 0, 0);

	glfwPollEvents();
	return continueGame;
}


void Window::Destroy(void)
{
	glfwTerminate();
}
