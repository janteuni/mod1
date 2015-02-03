#include "../include/Landscape.hpp"
#include <cstring>

Landscape::Landscape(void)
{
}

Landscape::Landscape(std::string file) : Model::Model()
{
	std::ifstream 	fs;
	std::string		str;
//	Vertex3 		point;
//	Vertex3			vertices[3];

	fs.open(file.c_str());
	if (!fs) {
		// trow exception;
		exit(0);
	}
	while (std::getline(fs, str)) {
		std::cout << str << std::endl;
	}
	fs.close();

}

Landscape::~Landscape(void)
{
}

Landscape & Landscape::operator=(Landscape const & ref)
{
	Model::operator=(ref);
	return *this;
}
