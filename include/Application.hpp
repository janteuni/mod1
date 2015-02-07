#ifndef _APPLICATION_H
# define _APPLICATION_H

# include <iostream>
# include "WindowManager.hpp"
# include "Model.hpp"
# include "Landscape.hpp"
# include "Cube.hpp"
# include "Water.hpp"
# include "TimeManager.hpp"
# include "Camera.hpp"
# include "InputManager.hpp"

# define BASIC 1
# define WAVE 2
# define RISE 3
# define RAIN 4


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
		void			setScenario(int scenario);
		int				getScenario(void) const;
		Cube * 			getCube(void) const;
		Water *			getWater(void) const;
		Landscape *		getLandscape(void) const;

	private:
		Application(Application const & ref);

		int				_scenario;
		WindowManager * _WM;
		Camera * 		_camera;
		Landscape *		_landscape;
		Cube *			_cube;
		Water *			_water;
};

#endif
