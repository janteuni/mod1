#include "../include/Droplet.hpp"

Droplet::Droplet(void)
{
	this->init();
}

Droplet::~Droplet(void)
{
}

Droplet & Droplet::operator=(Droplet const & ref)
{
	static_cast<void>(ref);
	return *this;
}

void Droplet::pushPoint(std::vector<Vertex3> * tab, float x, float y, float z, int color)
{
	Vertex3		point;

	point.xyz = vec3(x ,y ,z);
	if (color == 1)
		point.rgba = vec4(0.145f , 0.627f, 0.537f, 1.0f);
	else
		point.rgba = vec4(0.145f , 0.627f, 0.537f, 0.1f);
	tab->push_back(point);
}

void Droplet::init(void)
{
	std::vector<Vertex3>	tab;

	//face
	this->pushPoint(&tab, 0, 0, 0, 0);
	this->pushPoint(&tab, 0.1, 0, 0, 0);
	this->pushPoint(&tab, 0, 0.5, 0, 1);
	this->pushPoint(&tab, 0, 0.5, 0, 1);
	this->pushPoint(&tab, 0.1, 0, 0, 0);
	this->pushPoint(&tab, 0.1, 0.5, 0, 1);

	Vertex3 * vertab = &tab[0];
	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
}
