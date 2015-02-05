#include "../include/Cube.hpp"

Cube::Cube(void) : _width(1)
{
	this->init();
}

Cube::Cube(int w) : _width(w)
{
	this->init();
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

void Cube::pushPoint(std::vector<Vertex3> * tab, int x, int y, int z)
{
	Vertex3		point;

	point.xyz = vec3(x ,y ,z);
	point.rgba = vec4(1 , 0, 0, 1);
	tab->push_back(point);
}

void Cube::init(void)
{
	std::vector<Vertex3>	tab;

	//face
	this->pushPoint(&tab, 0, 0, 0);
	this->pushPoint(&tab, 1, 0, 0);
	this->pushPoint(&tab, 0, 1, 0);
	this->pushPoint(&tab, 1, 0, 0);
	this->pushPoint(&tab, 0, 1, 0);
	this->pushPoint(&tab, 1, 1, 0);

	//up
	this->pushPoint(&tab, 0, 0, 0);
	this->pushPoint(&tab, 1, 0, 0);
	this->pushPoint(&tab, 0, 0, 1);
	this->pushPoint(&tab, 1, 0, 0);
	this->pushPoint(&tab, 0, 0, 1);
	this->pushPoint(&tab, 1, 0, 1);

	//bot
	this->pushPoint(&tab, 0, 0, 1);
	this->pushPoint(&tab, 1, 0, 1);
	this->pushPoint(&tab, 0, 1, 1);
	this->pushPoint(&tab, 1, 0, 1);
	this->pushPoint(&tab, 0, 1, 1);
	this->pushPoint(&tab, 1, 1, 1);

	//left
	this->pushPoint(&tab, 0, 0, 0);
	this->pushPoint(&tab, 0, 0, 1);
	this->pushPoint(&tab, 0, 1, 0);
	this->pushPoint(&tab, 0, 0, 1);
	this->pushPoint(&tab, 0, 1, 0);
	this->pushPoint(&tab, 0, 1, 1);

	//right
	this->pushPoint(&tab, 1, 0, 0);
	this->pushPoint(&tab, 1, 1, 0);
	this->pushPoint(&tab, 1, 0, 1);
	this->pushPoint(&tab, 1, 1, 0);
	this->pushPoint(&tab, 1, 0, 1);
	this->pushPoint(&tab, 1, 1, 1);

	Vertex3 * vertab = &tab[0];
	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
}
