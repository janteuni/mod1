#include "../include/Landscape.hpp"
#include <cstring>
#include <cstdlib>
#include <vector>

Landscape::Landscape(void) : _width(50), _height(50)
{
}

Landscape::Landscape(std::string file) : Model::Model(), _width(50), _height(50)
{

	std::ifstream		  	fs;
	std::string				str;

	this->_highestPoint = 0.0f;

	fs.open(file.c_str());
	if (!fs) {
		// trow exception;
		exit(0);
	}

	// init map with 4 points
	this->setStartPoints();

	// read the file
	while (std::getline(fs, str)) {
		Vertex3 *		point = new Vertex3();
		std::string		tmp;
		int				index;

		if (str == "" || str.substr(0, 2) == "//") {
			continue;
		}

		index = str.find(' ');
		tmp = str.substr(0, index);
		point->xyz.x = std::atoi(tmp.c_str());
		str.erase(0, index + 1);

		index = str.find(' ');
		tmp = str.substr(0, index);
		point->xyz.y = std::atoi(tmp.c_str());
		str.erase(0, index + 1);

		index = str.find(' ');
		tmp = str.substr(0, index);
		point->xyz.z = std::atoi(tmp.c_str());
		str.erase(0, index + 1);

		if (point->xyz.y > this->_highestPoint) {
			this->_highestPoint = point->xyz.y;
		}
		this->_tabPoints.push_back(point);
	}
	fs.close();
	// generae the landscape
	this->setMap();
	this->generatePlan();
}

Landscape::~Landscape(void)
{
}

Landscape & Landscape::operator=(Landscape const & ref)
{
	Model::operator=(ref);
	this->_width = ref.getWidth();
	this->_height = ref.getHeight();
	this->_tabPoints = ref.getTabPoints();
	this->_highestPoint = ref.getHighestPoint();
	this->_map = ref.getMap();
	return *this;

}

int Landscape::getWidth(void) const
{
	return this->_width;
}

int Landscape::getHeight(void) const
{
	return this->_height;
}

float Landscape::getHighestPoint(void) const
{
	return this->_highestPoint;
}

std::vector<Vertex3 *> Landscape::getTabPoints(void) const
{
	return this->_tabPoints;
}

std::vector< std::vector<float> > Landscape::getMap(void) const
{
	return this->_map;
}

void Landscape::setMap(void)
{
	float y;
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			y = this->getWeigth(x, z);
			this->_map[x].push_back(y);
		}
	}
}

void Landscape::setStartPoints(void)
{
	this->_tabPoints.push_back(new Vertex3(vec3(0,0,0), vec4(0,1,0,1)));
	this->_tabPoints.push_back(new Vertex3(vec3(0,0,49), vec4(0,1,0,1)));
	this->_tabPoints.push_back(new Vertex3(vec3(49,0,49), vec4(0,1,0,1)));
	this->_tabPoints.push_back(new Vertex3(vec3(49,0,0), vec4(0,1,0,1)));
}

float Landscape::getDistance(vec3 xyz, int x, int z) const
{
	return sqrt( pow(( xyz.x - x), 2) + pow((xyz.z - z), 2) );
}

float Landscape::getWeigth(int x, int z)
{
	float sum1 = 0;
	float sum2 = 0;
	std::vector<Vertex3 *>::iterator it;

	for (it = this->_tabPoints.begin(); it < this->_tabPoints.end(); it++)
	{
		float d = this->getDistance((*it)->xyz, x, z);
		if (x == (*it)->xyz.x && z == (*it)->xyz.z) {
			return (*it)->xyz.y;
		}
		float w = 1 / pow(d, 1.5);
		sum1 = sum1 + ((*it)->xyz.y / pow(d, 1.5));
		sum2 = sum2 + w;
	}
	return sum1 / sum2;
}

void Landscape::pushPoint(std::vector<Vertex3> * tab, int x, int z)
{
	float 					y;
	float 					r;
	Vertex3					point;

	y = this->_map[x][z];
	if (this->_highestPoint > 0)
		r = y / this->_highestPoint;
	else
		r = 0.0f;
	point.xyz = vec3(x ,y , z);
	point.rgba = vec4(1 * r, 1, 0, 1);
	tab->push_back(point);
}

void Landscape::generatePlan(void)
{
	std::vector<Vertex3>	tab;

	for (int z = 0 ; z < this->_height - 1; z++) {
		for (int x = 0 ; x < this->_width - 1; x++) {
			this->pushPoint(&tab, x, z);
			this->pushPoint(&tab, x + 1, z);
			this->pushPoint(&tab, x, z + 1);
			this->pushPoint(&tab, x + 1, z);
			this->pushPoint(&tab, x + 1, z + 1);
			this->pushPoint(&tab, x, z + 1);
		}
	}

	Vertex3 * vertab = &tab[0];
	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
}
