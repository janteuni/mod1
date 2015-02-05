#include "../include/Water.hpp"

/*------------------- CONSTRUCTORS ---------------*/

Water::Water(void): _width(50), _height(50)
{
	float y = 0.0f;
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			this->_mapWater[x].push_back(y);
		}
	}
}

Water::~Water(void)
{
}

Water & Water::operator=(Water const & ref)
{
	this->_mapWater = ref.getMapWater();
	return *this;
}

std::vector<std::vector<float>> Water::getMapWater(void) const
{
	return this->_mapWater;
}

int Water::getWidth(void) const
{
	return this->_width;
}

int Water::getHeight(void) const
{
	return this->_height;
}

/* --------------- MAIN functions -----------------*/

void Water::updateWater(void)
{
}

void Water::averageZone(int x, int y)
{
	(void)x;
	(void)y;
}
