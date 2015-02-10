#ifndef _SHADER_H
# define _SHADER_H

# include <iostream>
# include <fstream>
# include "GL/glew.h"


class Shader
{
	public:

		Shader(void);
		Shader(Shader const & ref);
		~Shader(void);
		Shader & operator=(Shader const & ref);

		std::string LoadShaderFile(std::string strFile);
		void		Initialize(std::string strVertexFile, std::string strFragmentFile );
		GLint		GetVariable(std::string strVariable);

		GLuint		getVertexShaderId(void) const;
		GLuint		getFragmentShaderId(void) const;
		GLuint		getShaderProgramId(void) const;

		void		SetInt(GLint id, int newValue);
		void		SetFloat(GLint id, GLfloat newValue);
		void		SetFloat2(GLint id, GLfloat v0, GLfloat v1);
		void		SetFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2);
		void		SetFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		void		SetMatrix3(GLint id, GLsizei count, GLboolean transpose, const GLfloat * value);
		void		SetMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat * value);

		void		TurnOn(void);
		void		TurnOff(void);
		void		Destroy(void);

	private:

		GLuint		_vertexShaderId;
		GLuint		_fragmentShaderId;
		GLuint		_shaderProgramId;
};

#endif
