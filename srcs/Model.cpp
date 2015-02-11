#include "../include/Model.hpp"
#include <iostream>
/* ----------------------- CONSTRUCTOR ---------------------*/

Model::Model(void)
{
	this->_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Model::~Model(void)
{
	this->Destroy();
}

Model & Model::operator=(Model const & ref)
{
	this->_sh = ref.getShader();
	this->_vertices = ref._vertices;
	this->_verticesLength = ref.getVerticesLength();
	this->_vertexBufferId = ref.getVertexBufferId();
	this->_vertexArrayObjectId = ref.getVertexArrayObjectId();

	this->_position = ref.GetPosition();
	this->_rotation = ref.GetRotation();
	this->_scale = ref.GetScale();
	this->_viewMatrix = ref._viewMatrix;
	this->_projectionMatrix = ref._projectionMatrix;
	this->_camera = ref._camera;
	return *this;
}

Shader Model::getShader(void) const
{
	return this->_sh;
}

Vertex3 * Model::getVertices(void) const
{
	return this->_vertices;
}

GLint Model::getVerticesLength(void) const
{
	return this->_verticesLength;
}

GLuint Model::getVertexBufferId(void) const
{
	return this->_vertexBufferId;
}

GLuint Model::getVertexArrayObjectId(void) const
{
	return this->_vertexArrayObjectId;
}

glm::vec3 Model::GetPosition(void) const
{
	return this->_position;
}

void Model::SetPosition(glm::vec3 position)
{
	this->_position = position;
}

glm::vec3 Model::GetRotation(void) const
{
	return this->_rotation;
}

void Model::SetRotation(glm::vec3 rotation)
{
	this->_rotation = rotation;
}

glm::vec3 Model::GetScale(void) const
{
	return this->_scale;
}

void Model::SetScale(glm::vec3 scale)
{
	this->_scale = scale;
}

void Model::SetViewMatrix(glm::mat4 viewMatrix)
{
	this->_viewMatrix = viewMatrix;
}

void Model::SetProjectionMatrix(glm::mat4 projectionMatrix)
{
	this->_projectionMatrix  = projectionMatrix;
}

void Model::SetCamera(Camera * camera)
{
	this->_camera = camera;
}

Camera * Model::GetCamera(void)
{
	return this->_camera;
}

/* ----------------------- MAIN FUNCTION ---------------------*/

void Model::Initialize(Vertex3 vertices[], GLint length, std::string strVertex, std::string strFragment)
{
	this->_sh.Initialize(strVertex, strFragment);

	this->_vertices = vertices;
	this->_verticesLength = length;

	GLenum ErrorCheckValue = glGetError();

	glGenVertexArrays(1, &this->_vertexArrayObjectId);
	glBindVertexArray(this->_vertexArrayObjectId);

	glGenBuffers(1, &this->_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vertexBufferId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_vertices[0]) * length, this->_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(kVertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(this->_vertices[0]), 0);
	glVertexAttribPointer(kColorIndex, 4, GL_FLOAT, GL_FALSE, sizeof(this->_vertices[0]), (GLvoid*)sizeof(this->_vertices[0].xyz));
	glVertexAttribPointer(kNormalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(this->_vertices[0]), (GLvoid*)(sizeof(this->_vertices[0].xyz) + sizeof(this->_vertices[0].rgba)));

	ErrorCheckValue = glGetError();
	if ( ErrorCheckValue != GL_NO_ERROR )
	{
		std::cout << "ERROR: Could not create a VAO and VBO with error Id: " <<  ErrorCheckValue << std::endl;
		exit(-1);
	}
}

void Model::Render()
{
	this->_sh.TurnOn();

	glm::mat4 projectionMatrix = this->_camera->GetProjectionMatrix();
	glm::mat4 viewMatrix = this->_camera->GetViewMatrix();
	glm::vec3 lightPos(-50.5f, 100.8f, 159.0f);
	glm::vec3 lightCol(1.0f, 1.0f, 1.0f);

	glm::mat4 modelMatrix = translate(glm::mat4(1.0f), this->_position);

	modelMatrix = scale(modelMatrix, this->_scale);
	modelMatrix = rotate(modelMatrix, this->_rotation.x, glm::vec3(1, 0, 0));// x-axis
	modelMatrix = rotate(modelMatrix, this->_rotation.y, glm::vec3(0, 1, 0));// y-axis
	modelMatrix = rotate(modelMatrix, this->_rotation.z, glm::vec3(0, 0, 1));// z-axis


	GLint modelMatrixId = this->_sh.GetVariable("modelMatrix");
	GLint viewMatrixId = this->_sh.GetVariable("viewMatrix");
	GLint projectionMatrixId = this->_sh.GetVariable("projectionMatrix");
	GLint lightPositionId = this->_sh.GetVariable("light_pos");
	GLint lightColorId = this->_sh.GetVariable("light_intensities");

	this->_sh.SetMatrix4(modelMatrixId, 1, false, &modelMatrix[0][0]);
	this->_sh.SetMatrix4(viewMatrixId, 1, false, &viewMatrix[0][0]);
	this->_sh.SetMatrix4(projectionMatrixId, 1, false, &projectionMatrix[0][0]);

	this->_sh.SetFloat3(lightPositionId, lightPos.x, lightPos.y, lightPos.z);
	this->_sh.SetFloat3(lightColorId, lightCol.x, lightCol.y, lightCol.z);

	glBindVertexArray(this->_vertexArrayObjectId);

	glEnableVertexAttribArray(kVertexIndex);
	glEnableVertexAttribArray(kColorIndex);
	glEnableVertexAttribArray(kNormalIndex);

	glDrawArrays(GL_TRIANGLES, 0, this->_verticesLength);

	glDisableVertexAttribArray(kVertexIndex);
	glDisableVertexAttribArray(kColorIndex);
	glDisableVertexAttribArray(kNormalIndex);

	glBindVertexArray(0);

	this->_sh.TurnOff();
}


void Model::Destroy()
{
	if (this->_vertexBufferId) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &this->_vertexBufferId);
		this->_vertexBufferId = 0;
	}
	if(this->_vertexArrayObjectId) {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &this->_vertexArrayObjectId);
		this->_vertexArrayObjectId = 0;
	}
	this->_camera = nullptr;
	this->_sh.Destroy();
}
