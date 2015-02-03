#ifndef _LANDSCAPE_HPP
# define _LANDSCAPE_HPP

# include "Model.hpp"


class Landscape : public Model
{
	public:

		Landscape(void);
		Landscape(std::string file);
		~Landscape(void);
		Landscape & 	operator=(Landscape const & ref);

	private:

		Landscape(Landscape const & ref);
};

#endif
