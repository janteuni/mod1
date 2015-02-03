#ifndef _ModelManager_H
# define _ModelManager_H

# define GLM_FORCE_RADIANS

# include <iostream>
# include <stdlib.h>
# include "GL/glew.h"
# include "Shader.hpp"
# include "Vertex3.hpp"
# include "Camera.hpp"
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtx/transform2.hpp>

using namespace glm;

class Model
{
	public:

		static const GLuint kVertexIndex = 0;
		static const GLuint kColorIndex = 1;
		static const GLuint kTextureIndex = 2;
		static const GLuint kNormalIndex = 3;

		Model(void);
		~Model(void);
		Model & 	operator=(Model const & ref);

		Shader		getShader(void) const;
		Vertex3 *	getVertices(void) const;
		GLint		getVerticesLength(void) const;
		GLuint		getVertexBufferId(void) const;
		GLuint		getVertexArrayObjectId(void) const;

		vec3  		GetPosition() const;
		vec3  		GetRotation() const;
		vec3  		GetScale() const;
		void 		SetPosition(vec3 position);
		void 		SetRotation(vec3 rotation);
		void 		SetScale(vec3 scale);
		void 		SetViewMatrix(mat4 viewMatrix);
		void 		SetProjectionMatrix(mat4 projectionMatrix);
		Camera *	GetCamera(void);
		void 		SetCamera(Camera * pCamera);
		void 		Initialize(Vertex3 vertices[], int length, std::string strVertex, std::string strFragment);
		void 		Render(void);
		void 		Destroy(void);


	private:
		Model(Model const & ref);

		Vertex3 *	_vertices;
		GLint		_verticesLength;
		GLuint		_vertexBufferId;
		GLuint		_vertexArrayObjectId;

		vec3		_position;
		vec3		_rotation;
		vec3 		_scale;
		mat4		_viewMatrix;
		mat4		_projectionMatrix;

		Shader 		_sh;
		Camera *	_camera;
};

#endif
