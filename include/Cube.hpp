#ifndef CUBE_HPP
# define CUBE_HPP

# include <vector>
# include "Model.hpp"

class Cube : public Model
{
	public:

		Cube(void);
		~Cube(void);
		Cube(int w);
		Cube &			operator=(Cube const & ref);

		int				getWidth(void) const;
		void			init(void);

	private:

		Cube(Cube const & ref);

		int				_width;
};

#endif