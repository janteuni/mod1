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
		// throw exception;
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
	// generate the landscape
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

std::vector< std::vector<float> > const & Landscape::getMap(void) const
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
	this->_tabPoints.push_back(new Vertex3(glm::vec3(0,0,0), glm::vec4(0,1,0,1), glm::vec3(0, 1, 0)));
	this->_tabPoints.push_back(new Vertex3(glm::vec3(0,0,49), glm::vec4(0,1,0,1), glm::vec3(0, 1, 0)));
	this->_tabPoints.push_back(new Vertex3(glm::vec3(49,0,49), glm::vec4(0,1,0,1), glm::vec3(0, 1, 0)));
	this->_tabPoints.push_back(new Vertex3(glm::vec3(49,0,0), glm::vec4(0,1,0,1), glm::vec3(0, 1, 0)));
}

float Landscape::getDistance(glm::vec3 xyz, int x, int z) const
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

glm::vec3 Landscape::_getCrossProduct(glm::vec3 a, glm::vec3 b, int x, int z)
{
	glm::vec3 cp;

	a.y = this->_map[x][z] - this->_map[x + static_cast<int>(a.x)][z + static_cast<int>(a.z)];
	b.y = this->_map[x][z] - this->_map[x + static_cast<int>(b.x)][z + static_cast<int>(b.z)];
	cp.x = ((a.y * b.z) - (a.z * b.y));
	cp.z = ((a.x * b.y) - (a.y * b.x));
	cp.y = ((a.z * b.x) - (a.x * b.z));

	return cp;
}

glm::vec3 Landscape::_calcNorm(int x, int z)
{
/*
	for each vertex v do {
		VertexNormal n = { 0,0,0 };
		for each face f adjacent to v do {
			n += f.getNormal();
		}
		n.normalize();
		glNormal(n);
		glVertex3f(v.point());
	}
	*/
	glm::vec3 norm(0, 0, 0);
	glm::vec3 cp;

	// Face number one
	if (x - 1 >= 0 && z - 1 >= 0)
	{
		 /*a.x = -1;
		 a.z = 0;
		 a.y = map[x][z] - map[x - 1][z];
		 b.x = 0;
		 b.z = -1;
		 b.y = map[x][z] - map[x][z - 1];

		 norm.x += ((a.y * b.z) - (a.z * b.y));
		 norm.z += ((a.x * b.y) - (a.y * b.x));
		 norm.y += ((a.z * b.x) - (a.x * b.z));*/
		glm::vec3 a(-1, 0 ,0);
		glm::vec3 b(0, 0, -1);
		cp = this->_getCrossProduct(a, b, x, z);
		norm.x += cp.x;
		norm.y += cp.y;
		norm.z += cp.z;
	}
	// Face number two
	if (x + 1 < 50 && z - 1 >= 0)
	{
		glm::vec3 a(0, 0, -1);
		glm::vec3 b(1, 0, -1);
		cp = this->_getCrossProduct(a, b, x, z);
		norm.x += cp.x;
		norm.y += cp.y;
		norm.z += cp.z;
	}
	//Face number 3
	if (x + 1 < 50 && z - 1 >= 0)
	{
		glm::vec3 a(1, 0, -1);
		glm::vec3 b(1, 0, 0);
		cp = this->_getCrossProduct(a, b, x, z);
		norm.x += cp.x;
		norm.y += cp.y;
		norm.z += cp.z;

	}
	//Face number 4
	if (x + 1 < 50 && z + 1 < 50)
	{
		glm::vec3 a(1, 0, 0);
		glm::vec3 b(0, 0, 1);
		cp = this->_getCrossProduct(a, b, x, z);
		norm.x += cp.x;
		norm.y += cp.y;
		norm.z += cp.z;

	}
	//Face number 5
	if (x - 1 >= 0 && z + 1 < 50)
	{
		glm::vec3 a(0, 0, 1);
		glm::vec3 b(-1, 0, 1);
		cp = this->_getCrossProduct(a, b, x, z);
		norm.x += cp.x;
		norm.y += cp.y;
		norm.z += cp.z;

	}
	//Face number 6
	if (x - 1 >= 0 && z + 1 < 50)
	{
		glm::vec3 a(-1, 0, 1);
		glm::vec3 b(-1, 0, 0);
		cp = this->_getCrossProduct(a, b, x, z);
		norm.x += cp.x;
		norm.y += cp.y;
		norm.z += cp.z;

	}
	normalize(norm);
	return norm;
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
	point.xyz = glm::vec3(x ,y ,z);
	point.rgba = glm::vec4(1 * r, 1, 0, 1);
	point.norm = this->_calcNorm(x, z);
	//point.norm = glm::vec3(0);
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
