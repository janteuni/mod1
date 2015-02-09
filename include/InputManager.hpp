#ifndef _INPUTMANAGER_H
# define _INPUTMANAGER_H

# define GLM_FORCE_RADIANS

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtx/transform2.hpp>
# include "Camera.hpp"

enum InputCodes
{
	kEscape = 27,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,
};

class InputManager
{
	public:

		InputManager(void);
		~InputManager(void);

		void 		KeyPressed(InputCodes code);
		void 		SetCamera(Camera * ptr);
		Camera *	GetCamera(void) const;
		void 		MouseMoved(float mouseX, float mouseY);

	protected:

		InputManager(InputManager const & ref);
		InputManager & operator=(InputManager const & ref);

		Camera * 	_camera;
};

#endif
