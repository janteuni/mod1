#include "../include/Landscape.hpp"
#include <cstring>
#include <cstdlib>
#include <vector>

Landscape::Landscape(void) : _width(50), _height(50)
{
}

Landscape::Landscape(std::string file) : Model::Model(), _width(50), _height(50)
{

//	this->generatePlan();
	std::ifstream 			fs;
	std::string				str;
	Vertex3 				point;
	std::vector<Vertex3>	tab;

	fs.open(file.c_str());
	if (!fs) {
		// trow exception;
		exit(0);
	}
	point.xyz = vec3(0,0,0);
	tab.push_back(point);
	point.xyz = vec3(0,0,49);
	tab.push_back(point);
	point.xyz = vec3(49,0,49);
	tab.push_back(point);
	point.xyz = vec3(49,0,0);
	tab.push_back(point);

	while (std::getline(fs, str)) {
		std::string	tmp;
		int			index;

		if (str == "") {
			continue;
		}

		if (str.substr(0, 2) == "//") {
			continue;
		}

		index = str.find(' ');
		tmp = str.substr(0, index);
		point.xyz.x = std::atoi(tmp.c_str());
		str.erase(0, index + 1);

		index = str.find(' ');
		tmp = str.substr(0, index);
		point.xyz.y = std::atoi(tmp.c_str());
		str.erase(0, index + 1);

		index = str.find(' ');
		tmp = str.substr(0, index);
		point.xyz.z = std::atoi(tmp.c_str());
		str.erase(0, index + 1);

/*		if (str == "red") {
			point.rgba = vec4(1, 0, 0, 1);
		}

		if (str == "green") {
			point.rgba = vec4(0, 1, 0, 1);
		}

		if (str == "blue") {
			point.rgba = vec4(0, 0, 1, 1);
		}*/

		tab.push_back(point);
	}
	fs.close();
	this->generatePlan(tab);

//	Vertex3 * vertab = &tab[0];

//	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
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

float distance(Vertex3 a, int x, int z)
{
	return sqrt( pow(( a.xyz.x - x), 2) + pow((a.xyz.z - z), 2) );
}

float hauteur(std::vector<Vertex3> points, int x, int z)
{
	float sum1 = 0;
	float sum2 = 0;

	int i;


	for(i = 0; i < 6; i++){
		float d = distance(points[i], x, z);
		if (x == points[i].xyz.x && z == points[i].xyz.z) {
			return points[i].xyz.y;
		}
		float w = 1 / pow(d, 1.5);
		sum1 = sum1 + (points[i].xyz.y / pow(d, 1.5));
		sum2 = sum2 + w;
	}
	return sum1 / sum2;
}

void Landscape::generatePlan(std::vector<Vertex3> points)
{

	Vertex3 				point;
	std::vector<Vertex3>	tab;

	for (int z = 0; z < this->_height - 1; z++) {
		for (int x = 0; x < this->_width - 1; x++) {

			// first triangle
			float y =  hauteur(points, x, z);
			point.xyz = vec3(x ,y , z);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  hauteur(points, x + 1, z);
			point.xyz = vec3(x + 1 , y, z);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  hauteur(points, x, z - 1);
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
			y =  hauteur(points, x + 1, z);
			point.xyz = vec3(x + 1 , y, z);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  hauteur(points, x + 1, z - 1);
			point.xyz = vec3(x + 1 , y, z - 1);
			if (y  > 8) {
				point.rgba = vec4(0, 1, 0, 1);
			} else if (y > 15) {
				point.rgba = vec4(0, 0, 1, 1);	
			} else {
				point.rgba = vec4(1, 0, 0, 1);
			}
			tab.push_back(point);

			y =  hauteur(points, x, z - 1);
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
