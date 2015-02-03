#include "../include/Vertex3.hpp"

Vertex3::Vertex3(void)
{
	this->xyz = vec3(0);
	this->rgba = vec4(0);
}

Vertex3::Vertex3(vec3 pos, vec4 color)
{
	this->xyz = pos;
	this->rgba = color;
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
	return *this;
}
