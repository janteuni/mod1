#ifndef _WINDOWMANAGER_H
# define _WINDOWMANAGER_H

# include <string>
# include "InputManager.hpp"

class WindowManager
{
	public:

		virtual ~WindowManager(void);
		WindowManager(void);

		virtual int 		Initialize(int width, int height, std::string strTitle, bool bFullScreen = false) = 0;
		virtual void 		SwapTheBuffers(void) = 0;
		virtual bool 		ProcessInput(bool continueGame) = 0;
		virtual void 		Destroy(void) = 0;
		virtual InputManager * GetInputManager(void);

	protected:
		InputManager	inputManager;
		WindowManager(WindowManager const & ref);
		WindowManager & operator=(WindowManager const & ret);
};

#endif
