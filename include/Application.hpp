#ifndef _APPLICATION_H
# define _APPLICATION_H

# include <iostream>
# include "WindowManager.hpp"
# include "Model.hpp"
# include "Landscape.hpp"
# include "Cube.hpp"
# include "TimeManager.hpp"
# include "Camera.hpp"
# include "InputManager.hpp"

class Application
{
	public:
		static const int ScreenWidth = 1200;
		static const int ScreenHeight = 1000;

		Application(void);
		~Application(void);
		Application & operator=(Application const & ref);

		int				GLMain(std::string file);
		WindowManager * GetWindowManager(void) const;
		void 			SetWindowManager(WindowManager * ptrWM);
		void 			Initialize(std::string file);
		void 			GameLoop(void);
		void 			Destroy(void);
		Camera *		GetCamera(void) const;
		void			SetCamera(Camera * ptr);

	private:
		Application(Application const & ref);

		WindowManager * _WM;
		Camera * 		_camera;
		Model *			_landscape;
		Model *			_cube;
};

#endif
