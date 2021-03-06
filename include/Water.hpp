#ifndef WATER_HPP
# define WATER_HPP

# define BASIC 1
# define WAVE 2
# define RISE 3
# define EMPTY 4
# define RAIN 5

# include <glm/glm.hpp>
# include <iostream>
# include <vector>
# include <list>
# include <cmath>
# include <stdlib.h>
# include <time.h>



class Water
{
	public:

		Water(void);
		Water(int scenario);
		~Water(void);
		Water &								operator=(Water const & ref);
		std::vector< std::vector<float>> const &	getMapWater(void) const;
		int									getWidth(void) const;
		int									getHeight(void) const;
		std::list < glm::vec3 > const &		getRain(void) const;
		void								updateWater(void);
		void								removeWater(void);
		void								averageZone(int x, int z, std::vector< std::vector<float> > const & land);
		void								setWater(int x, int z, float water);
		void								addWater(int x, int z, float water);
		void 								addDroplet(void);
		void 								rainfall(std::vector<std::vector<float>> const & land);
		void								init(void);

	private:

		Water(Water const & ref);
		int									_width;
		int									_height;
		int									_scenario;
		std::vector< std::vector<float> > 	_mapWater = std::vector< std::vector<float> >(50);
		std::list< glm::vec3 >				_rain;
};

#endif
