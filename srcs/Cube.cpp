#include "../include/Cube.hpp"

Cube::Cube(void) : _width(1)
{
}

Cube::Cube(int w) : _width(w)
{
}

Cube::~Cube(void)
{
}

Cube & Cube::operator=(Cube const & ref)
{
	this->_width = ref.getWidth();
	return *this;
}

int Cube::getWidth(void) const
{
	return this->_width;
}

void Cube::init(void)
{
	std::vector<Vertex3>	tab;

	Vertex3 * vertab = &tab[0];
	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
}
