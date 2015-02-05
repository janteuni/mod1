#ifndef _LANDSCAPE_HPP
# define _LANDSCAPE_HPP

# include "Model.hpp"


#include <vector>
#include <cmath>
class Landscape : public Model
{
	public:

		Landscape(void);
		Landscape(std::string file);
		~Landscape(void);
		Landscape & 			operator=(Landscape const & ref);
		int						getWidth(void) const;
		int						getHeight(void) const;
		void					generatePlan(void);
		float     				getDistance(vec3 xyz, int x, int y) const;
		float     				getWeigth(int x, int z);
		void					setStartPoints(void);
		void					pushPoint(std::vector<Vertex3> * tab, int x, int z);

	private:

		Landscape(Landscape const & ref);
		int                     _width;
		int			            _height;
		std::vector<Vertex3 *>  _tabPoints;
		float                   _highestPoint;
};

#endif
