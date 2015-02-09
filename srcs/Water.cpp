#include "../include/Water.hpp"

/*------------------- CONSTRUCTORS ---------------*/

Water::Water(void): _width(50), _height(50), _scenario(1)
{
	this->init();
}

Water::Water(int scenario) : _width(50), _height(50), _scenario(scenario)
{
	srand (time(NULL));

	this->init();
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

std::list< glm::vec3 > const &  Water::getRain(void) const
{
	return this->_rain;
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
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			if (this->_mapWater[x][z] > 0.000000f)
				this->addWater(x, z, 0.05f);
		}
	}
}

void Water::removeWater(void)
{
	if (this->_mapWater[0][0] > 0.000000f) {
		this->_mapWater[0][0] = this->_mapWater[0][0] - 1.0f;
	}
	if (this->_mapWater[0][49] > 0.000000f) {
		this->_mapWater[0][49] = this->_mapWater[0][49] - 1.0f;
	}
	if (this->_mapWater[49][49] > 0.000000f) {
		this->_mapWater[49][49] = this->_mapWater[49][49] - 1.0f;
	}
	if (this->_mapWater[49][0] > 0.000000f) {
		this->_mapWater[49][0] = this->_mapWater[49][0] - 1.0f;
	}
}

void Water::init(void)
{
	float y = (this->_scenario == BASIC ? 2.0f : 0.0f);

	//create water layer
	for (int x = 0 ; x < this->_width; x++) {
		for (int z = 0 ; z < this->_height; z++) {
			if (this->_scenario == WAVE && z == 0)
				this->_mapWater[x].push_back(100.0f);
			else
				this->_mapWater[x].push_back(y);
		}
	}

	if (this->_scenario == RISE ||this->_scenario == EMPTY) {
		this->addWater(0, 0, 1);
		this->addWater(0, 49, 1);
		this->addWater(49, 0, 1);
		this->addWater(49, 49, 1);
	} else if (this->_scenario == RAIN) {
		for (int x = 10; x > 0; x--)
			this->addDroplet();
	}

}

void Water::averageZone(int x, int z, std::vector<std::vector<float>> const & land)
{
	float near = 0.000000f;
	float me = 0.000000f;
	int littleX = -1;
	int littleZ = -1;
	float diff = 0.0f;
	float gift = 0.0f;

	if (this->_mapWater[x][z] <= 0.000000f) {
		return ;
	}

	me = this->_mapWater[x][z] + land[x][z];

	// check each case around you ans save in littleX and littleZ the smallest height
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

	// give a 'gift' of water to the smallest height
	if (littleX != -1) {
		near = this->_mapWater[littleX][littleZ] + land[littleX][littleZ];
		diff = (me - near) / 2;
		gift = (this->_mapWater[x][z] >= diff) ? diff : this->_mapWater[x][z];
		this->_mapWater[littleX][littleZ] = this->_mapWater[littleX][littleZ] + gift;
		this->_mapWater[x][z] = this->_mapWater[x][z] - gift;
	}
}

void Water::addDroplet(void)
{
	int x = rand() % 49 + 0;
	int z = rand() % 49 + 0;

	this->_rain.push_back(glm::vec3(x, 40, z));
}

void Water::rainfall(std::vector<std::vector<float>> const & land)
{
	for (std::list< glm::vec3 >::iterator it = this->_rain.begin(); it != this->_rain.end(); ++it)
	{
		it->y = it->y - 1;
		if (it->y <= this->_mapWater[it->x][it->z] || it->y <= land[it->x][it->z]){
			this->addWater(it->x, it->z, 0.5); // 1 == amount of water added to land
			this->_rain.erase(it);
		}
	}
}

