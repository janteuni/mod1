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
		Landscape & 	operator=(Landscape const & ref);
		int				getWidth(void) const;
		int				getHeight(void) const;
		void			generatePlan(std::vector<Vertex3>  points);

	private:

		Landscape(Landscape const & ref);
		int			_width;
		int			_height;
};

#endif
