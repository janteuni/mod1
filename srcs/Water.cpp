#include "../include/Water.hpp"

/*------------------- CONSTRUCTORS ---------------*/

Water::Water(void): _width(50), _height(50)
{
	// scenario1 = water in all map
/*	float y = 2.0f;
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			this->_mapWater[x].push_back(y);
		}
	}*/

	// scenario2 = wave
/*	float y = 0.0f;
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			if (z == 0) {
				this->_mapWater[x].push_back(100.0f);
			} else {
				this->_mapWater[x].push_back(y);
			}
		}
	}*/

	//scenario3 = rise of water
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

void Water::addWater(int x, int z, float water)
{
	this->_mapWater[x][z] = this->_mapWater[x][z] + water;
}

/* --------------- MAIN functions -----------------*/

void Water::updateWater(void)
{
}

void Water::averageZone(int x, int z, std::vector<std::vector<float>> const & land)
{
	float near = 0.000000f;
	float me = 0.000000f;
	int littleX = -1;
	int littleZ = -1;
	float diff = 0.0f;
	float gift = 0.0f;

	// check each case around you

	if (this->_mapWater[x][z] <= 0.000000f) {
		return ;
	}
	me = this->_mapWater[x][z] + land[x][z];
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = z - 1; j <= z + 1; j++) {
			if (i >= 0 && i < 50
					&& j >= 0 && j < 50) {
				near = this->_mapWater[i][j] + land[i][j];
				if (near < me) {
					if (littleX == -1 || near < this->_mapWater[littleX][littleZ] + land[littleX][littleZ]) {
						littleX = i;
						littleZ = j;
					}
				}
			}
		}
	}
	if (littleX != -1) {
		near = this->_mapWater[littleX][littleZ] + land[littleX][littleZ];
		diff = (me - near) / 2;
		gift = (this->_mapWater[x][z] >= diff) ? diff : this->_mapWater[x][z];
		this->_mapWater[littleX][littleZ] = this->_mapWater[littleX][littleZ] + gift;
		this->_mapWater[x][z] = this->_mapWater[x][z] - gift;
	}
}
