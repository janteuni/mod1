#include "../include/Landscape.hpp"
#include <cstring>
#include <cstdlib>
#include <vector>

Landscape::Landscape(void) : _width(50), _height(50)
{
}

Landscape::Landscape(std::string file) : Model::Model(), _width(50), _height(50)
{

	std::ifstream		  fs;
	std::string		str;

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

		this->_tabPoints.push_back(point);
	}
	fs.close();
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

void Landscape::generatePlan(void)
{

	Vertex3		  point;
	std::vector<Vertex3>	tab;

	for (int z = 0 ; z < this->_height - 1; z++) {
		for (int x = 0 ; x < this->_width - 1; x++) {

			// first triangle
			float y =  getWeigth(x, z);
			point.xyz = vec3(x ,y , z);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  getWeigth(x + 1, z);
			point.xyz = vec3(x + 1 , y, z);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  getWeigth(x, z - 1);
			point.xyz = vec3(x , y, z - 1);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			//second triangle
			y =  getWeigth(x + 1, z);
			point.xyz = vec3(x + 1 , y, z);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  getWeigth(x + 1, z - 1);
			point.xyz = vec3(x + 1 , y, z - 1);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  getWeigth(x, z - 1);
			point.xyz = vec3(x , y, z - 1);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

		}
	}


	Vertex3 * vertab = &tab[0];
	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
}
