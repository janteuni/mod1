#include "../include/Shader.hpp"

Shader::Shader(void)
{
}

Shader::~Shader(void)
{
	this->Destroy();
}

Shader::Shader(Shader const & ref)
{
	*this = ref;
}

Shader & Shader::operator=(Shader const & ref)
{
	this->_vertexShaderId = ref.getVertexShaderId();
	this->_fragmentShaderId = ref.getFragmentShaderId();
	this->_shaderProgramId = ref.getShaderProgramId();
	return *this;
}

GLuint Shader::getVertexShaderId(void) const
{
	return this->_vertexShaderId;
}

GLuint Shader::getFragmentShaderId(void) const
{
	return this->_fragmentShaderId;
}

GLuint Shader::getShaderProgramId(void) const
{
	return this->_shaderProgramId;
}

/* ----------------------- TUNR ON / OFF ----------------------*/

void Shader::TurnOn(void)
{
	glUseProgram(this->_shaderProgramId);
}

void Shader::TurnOff(void)
{
	glUseProgram(0);
}

/* ----------------------- SET integer / matrix ----------------------*/

void Shader::SetInt(GLint id, int newValue)
{
	glUniform1i(id, newValue);
}

void Shader::SetFloat(GLint id, GLfloat newValue)
{
	glUniform1f(id, newValue);
}

void Shader::SetFloat2(GLint id, GLfloat v0, GLfloat v1)
{
	glUniform2f(id, v0, v1);
}

void Shader::SetFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(id, v0, v1, v2);
}

void Shader::SetFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(id, v0, v1, v2, v3);
}

void Shader::SetMatrix3(GLint id, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix3fv(id, count, transpose, value);
}

void Shader::SetMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix4fv(id, count, transpose, value);
}

/*------------------------- MAIN FUNCTION --------------------------------- */

std::string Shader::LoadShaderFile(std::string strFile)
{
	std::ifstream fin(strFile.c_str());

	if (!fin) {
		return "";
	}

	std::string strLine = "";
	std::string strText = "";

	while (getline(fin, strLine)) {
		strText = strText + "\n" + strLine;
	}
	fin.close();
	return strText;
}


void Shader::Initialize(std::string strVertexFile, std::string strFragmentFile)
{
	std::string strVShader, strFShader;

	if (!strVertexFile.length() || !strFragmentFile.length()) {
		return ;
	}

	if (this->_vertexShaderId || this->_fragmentShaderId || this->_shaderProgramId) {
		Destroy();
	}

	GLenum ErrorCheckValue = glGetError();

	this->_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	this->_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	strVShader = LoadShaderFile(strVertexFile.c_str());
	strFShader = LoadShaderFile(strFragmentFile.c_str());

	const char * szVShader = strVShader.c_str();
	const char * szFShader = strFShader.c_str();

	glShaderSource(this->_vertexShaderId, 1, &szVShader, nullptr);
	glShaderSource(this->_fragmentShaderId, 1, &szFShader, nullptr);

	glCompileShader(this->_vertexShaderId);
	glCompileShader(this->_fragmentShaderId);

	this->_shaderProgramId = glCreateProgram();

	glAttachShader(this->_shaderProgramId, this->_vertexShaderId);
	glAttachShader(this->_shaderProgramId, this->_fragmentShaderId);
	glLinkProgram(this->_shaderProgramId);

	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR) {
		std::cout << "ERROR: Could not create the shader program with error Id:" <<  ErrorCheckValue << std::endl;
		exit(-1);
	}
}

GLint Shader::GetVariable(std::string strVariable)
{
	if(!this->_shaderProgramId)
		return -1;
	return glGetUniformLocation(this->_shaderProgramId, strVariable.c_str());
}


void Shader::Destroy(void)
{
	if (this->_vertexShaderId) {
		glDetachShader(this->_shaderProgramId, this->_vertexShaderId);
		glDeleteShader(this->_vertexShaderId);
		this->_vertexShaderId = 0;
	}

	if (this->_fragmentShaderId) {
		glDetachShader(this->_shaderProgramId, this->_fragmentShaderId);
		glDeleteShader(this->_fragmentShaderId);
		this->_fragmentShaderId = 0;
	}
	if (this->_shaderProgramId) {
		glDeleteShader(this->_shaderProgramId);
		this->_shaderProgramId = 0;
	}
}
