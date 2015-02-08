#ifndef DROPLET_HPP
# define DROPLET_HPP

# include <vector>
# include "Model.hpp"

class Droplet : public Model
{
	public:

		Droplet(void);
		~Droplet(void);
		Droplet &			operator=(Droplet const & ref);

		void			init(void);
		void 			pushPoint(std::vector<Vertex3> * tab, float x, float y, float z, int color);

	private:

		Droplet(Droplet const & ref);

};

#endif
