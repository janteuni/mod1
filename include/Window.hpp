#ifndef _WINDOW_H
# define _WINDOW_H

# include <iostream>
# include "GLFW/glfw3.h"
# include "WindowManager.hpp"

class Window : public WindowManager
{
	public:

		Window(void);
		~Window(void);
		Window & operator=(Window const & ref);

		GLFWwindow *	getWindow(void) const;
		virtual int		Initialize(int width, int height, std::string strTitle, bool bFullScreen = false);
		virtual void	SwapTheBuffers(void);
		virtual bool	ProcessInput(bool continueGame);
		virtual void	Destroy(void);

	protected:
		Window(Window const & ref);
		GLFWwindow * 	_window;
};

#endif
