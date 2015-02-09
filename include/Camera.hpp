#ifndef _CAMERA_H
# define _CAMERA_H

# define PI 3.14159265358979323846264338327950288
# define GLM_FORCE_RADIANS

# include <iostream>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtx/transform2.hpp>

class Camera
{
	public:

		Camera(void);
		~Camera(void);
		Camera(Camera const & ref);
		Camera & operator=(Camera const & ref);

		glm::mat4 	SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
		glm::mat4 	GetRotationMatrix(void);
		glm::mat4 	GetProjectionMatrix(void) const;
		glm::mat4 	GetViewMatrix(void);
		glm::vec3 	GetPosition(void) const;

		void 		SetPosition(glm::vec3 position);

		glm::vec3 	GetView(void);
		glm::vec3	GetUp(void);
		glm::vec3 	GetRight(void);

		float		GetYaw(void) const;
		float		GetPitch(void) const;
		double 		GetSpeed(void) const;
		void		SetYaw(float yaw);
		void		SetPitch(float pitch);
		void		SetSpeed(double speed);
		void 		SetRotationSpeed(double speed);
		double 		GetRotationSpeed(void);
		void		SetViewByMouse(float mouseX, float mouseY);
		void 		PositionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch);
		void 		MoveCamera(float speed);
		void 		Strafe(float speed);

protected:

		glm::mat4 	_projectionMatrix;
		glm::vec3 	_position;

		double 		_mouseSpeed = 0.001;
		float 		_rotationSpeed = 2;
		float 		_speed = 9.0;
		float 		_yaw = 1.823;
		float 		_pitch = 0.0610029;
};


#endif
