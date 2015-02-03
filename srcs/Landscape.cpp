#include "../include/Landscape.hpp"
#include <cstring>
#include <cstdlib>
#include <vector>

Landscape::Landscape(void) : _width(50), _height(50)
{
}

Landscape::Landscape(std::string file) : Model::Model(), _width(50), _height(50)
{
	(void) file;

	this->generatePlan();
/*	std::ifstream 			fs;
	std::string				str;
	Vertex3 				point;
	std::vector<Vertex3>	tab;

	fs.open(file.c_str());
	if (!fs) {
		// trow exception;
		exit(0);
	}
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

		if (str == "red") {
			point.rgba = vec4(1, 0, 0, 1);
		}

		if (str == "green") {
			point.rgba = vec4(0, 1, 0, 1);
		}

		if (str == "blue") {
			point.rgba = vec4(0, 0, 1, 1);
		}

		tab.push_back(point);
	}
	fs.close();

	Vertex3 * vertab = &tab[0];

	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");*/
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

void Landscape::generatePlan(void)
{

	Vertex3 				point;
	std::vector<Vertex3>	tab;

	for (int z = 0; z < this->_height - 1; z++) {
		for (int x = 0; x < this->_width - 1; x++) {

			// first triangle
			point.xyz = vec3(x , 0, z);
			point.rgba = vec4(1, 0, 0, 1);
			tab.push_back(point);

			point.xyz = vec3(x + 1 , 0, z);
			point.rgba = vec4(1, 0, 0, 1);
			tab.push_back(point);

			point.xyz = vec3(x , 0, z - 1);
			point.rgba = vec4(1, 0, 0, 1);
			tab.push_back(point);

			//second triangle
			point.xyz = vec3(x + 1 , 0, z);
			point.rgba = vec4(1, 0, 0, 1);
			tab.push_back(point);

			point.xyz = vec3(x + 1 , 0, z - 1);
			point.rgba = vec4(1, 0, 0, 1);
			tab.push_back(point);

			point.xyz = vec3(x , 0, z - 1);
			point.rgba = vec4(1, 0, 0, 1);
			tab.push_back(point);

		}
	}


	Vertex3 * vertab = &tab[0];
	this->Initialize(vertab, tab.size(), "Shaders/Shader.vertex", "Shaders/Shader.fragment");
}
