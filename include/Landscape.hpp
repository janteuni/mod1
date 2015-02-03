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
		int				getWidth(void) const;
		int				getHeight(void) const;
		void			generatePlan(void);

	private:

		Landscape(Landscape const & ref);
		int			_width;
		int			_height;
};

#endif
