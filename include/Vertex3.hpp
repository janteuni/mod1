#ifndef VERTEX_H
# define VERTEX_H

# include <glm/glm.hpp>

class Vertex3
{
	public:
		Vertex3(void);
		Vertex3(glm::vec3 pos, glm::vec4 color, glm::vec3 norm);
		~Vertex3(void);
		Vertex3(Vertex3 const & ref);
		Vertex3 & operator=(Vertex3 const & ref);

		glm::vec3 xyz;
		glm::vec4 rgba;
		glm::vec3 norm;
};

#endif
