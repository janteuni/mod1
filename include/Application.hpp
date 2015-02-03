#ifndef _APPLICATION_H
# define _APPLICATION_H

# include "WindowManager.hpp"
# include "Model.hpp"
# include "TimeManager.hpp"
# include "Camera.hpp"
# include "InputManager.hpp"

class Application
{
	public:
		static const int ScreenWidth = 1024;
		static const int ScreenHeight = 768;

		Application(void);
		~Application(void);
		Application & operator=(Application const & ref);

		int				GLMain(void);
		WindowManager * GetWindowManager(void) const;
		void 			SetWindowManager(WindowManager * ptrWM);
		void 			Initialize(void);
		void 			GameLoop(void);
		void 			Destroy(void);
		Camera *		GetCamera(void) const;
		void			SetCamera(Camera * ptr);

	private:
		Application(Application const & ref);

		WindowManager * _WM;
		Camera * 		_camera;
};

#endif
