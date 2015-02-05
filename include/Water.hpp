#ifndef WATER_HPP
# define WATER_HPP

# include <vector>
# include <cmath>

class Water
{
	public:

		Water(void);
		~Water(void);
		Water &								operator=(Water const & ref);
		std::vector< std::vector<float>>	getMapWater(void) const;
		int									getWidth(void) const;
		int									getHeight(void) const;
		void								updateWater(void);
		void								averageZone(int x, int y);

	private:

		Water(Water const & ref);
		int									_width;
		int									_height;
		std::vector< std::vector<float> > 	_mapWater = std::vector< std::vector<float> >(50);
};

#endif
