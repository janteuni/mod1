#ifndef _CAMERA_H
# define _CAMERA_H

# define PI 3.14159265358979323846264338327950288
# define GLM_FORCE_RADIANS

# include <iostream>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtx/transform2.hpp>

using namespace glm;


class Camera
{
	public:

		Camera(void);
		~Camera(void);
		Camera(Camera const & ref);
		Camera & operator=(Camera const & ref);

		mat4 		SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
		mat4 		GetRotationMatrix(void);
		mat4 		GetProjectionMatrix(void) const;
		mat4 		GetViewMatrix(void);
		vec3 		GetPosition(void) const;

		void 		SetPosition(vec3 position);

		vec3 		GetView(void);
		vec3		GetUp(void);
		vec3 		GetRight(void);

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

		mat4 		_projectionMatrix;
		vec3 		_position;

		double 		_mouseSpeed = 0.001;
		float 		_rotationSpeed = 2;
		float 		_speed = 5.0;
		float 		_yaw = 0;
		float 		_pitch = 0;
};


#endif
