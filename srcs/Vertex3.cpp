#include "../include/Vertex3.hpp"

Vertex3::Vertex3(void)
{
	this->xyz = glm::vec3(0);
	this->rgba = glm::vec4(0);
	this->norm = glm::vec3(0);
}

Vertex3::Vertex3(glm::vec3 pos, glm::vec4 color, glm::vec3 norm)
{
	this->xyz = pos;
	this->rgba = color;
	this->norm = norm;
}

Vertex3::~Vertex3(void)
{
}

Vertex3::Vertex3(Vertex3 const & ref)
{
	*this = ref;
}

Vertex3 & Vertex3::operator=(Vertex3 const & ref)
{
	this->xyz = ref.xyz;
	this->rgba = ref.rgba;
	this->norm = ref.norm;
	return *this;
}
