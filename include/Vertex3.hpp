#ifndef VERTEX_H
# define VERTEX_H

# include <glm/glm.hpp>

using namespace glm;

class Vertex3
{
	public:
		Vertex3(void);
		Vertex3(vec3 pos, vec4 color);
		~Vertex3(void);
		Vertex3(Vertex3 const & ref);
		Vertex3 & operator=(Vertex3 const & ref);

		vec3 xyz;
		vec4 rgba;
};

#endif
