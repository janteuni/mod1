#include "../include/Water.hpp"

/*------------------- CONSTRUCTORS ---------------*/

Water::Water(void): _width(50), _height(50)
{
	float y = 1.0f;
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			this->_mapWater[x].push_back(y);
			//	y = y + 1.0f;
			//	if (y == 5.0f) {y = 1.0f;}
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

std::vector<std::vector<float>> const & Water::getMapWater(void) const
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

void Water::setWater(int x, int z, float water)
{
	this->_mapWater[x][z] = water;
}

/* --------------- MAIN functions -----------------*/

void Water::updateWater(void)
{
}

void Water::averageZone(int x, int z, std::vector<std::vector<float>> const & land)
{
	int y;

	// check each case around you
	for (int i = 0; i < 3; i++) {
		if (this->_mapWater[x][z] > 0 && x - 1 > 0 && z - 1 + i > 0 && z - 1 + i < 50) {
			y = this->_mapWater[x - 1][z - 1 + i] + land[x - 1][z - 1 + i];
			if (y < this->_mapWater[x][z] + land[x][z]) {
				this->_mapWater[x - 1][z - 1 + i] = this->_mapWater[x - 1][z - 1 + i] + 1.0f;
				this->_mapWater[x][z] = this->_mapWater[x][z] - 1.0f;
				break ;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (this->_mapWater[x][z] > 0 && x + 1 < 50 && z - 1 + i > 0 && z - 1 + i < 50) {
			y = this->_mapWater[x + 1][z - 1 + i] + land[x + 1][z - 1 + i];
			if (y < this->_mapWater[x][z] + land[x][z]) {
				this->_mapWater[x + 1][z - 1 + i] = this->_mapWater[x + 1][z - 1 + i] + 1.0f;
				this->_mapWater[x][z] = this->_mapWater[x][z] - 1.0f;
				break ;
			}
		}
	}
	if (this->_mapWater[x][z] > 0 && z - 1 > 0 && z - 1 < 50) {
		y = this->_mapWater[x][z - 1] + land[x][z - 1];
		if (y < this->_mapWater[x][z] + land[x][z]) {
			this->_mapWater[x][z - 1] = this->_mapWater[x][z - 1] + 1.0f;
			this->_mapWater[x][z] = this->_mapWater[x][z] - 1.0f;
		}
	}
	if (this->_mapWater[x][z] > 0 && z + 1 > 0 && z + 1 < 50) {
		y = this->_mapWater[x][z + 1] + land[x][z + 1];
		if (y < this->_mapWater[x][z] + land[x][z]) {
			this->_mapWater[x][z + 1] = this->_mapWater[x][z + 1] + 1.0f;
			this->_mapWater[x][z] = this->_mapWater[x][z] - 1.0f;
		}
	}
}
