#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>


namespace form {
    //    v6----- v5
    //   /|      /|
    //  v1------v2|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v0------v3

	const int CubeData::datas[] = {
		// Front v0,v3,v2,v1
		   0,  0,  0,       0,  0,  1,       1, 1,
	       1,  0,  0,       0,  0,  1,       1, 0,
		   1,  1,  0,       0,  0,  1,       0, 0,
           0,  1,  0,       0,  0,  1,       0, 1,
		  // Back v4,v7,v6,v5	
           1,  0,  1,       0,  0, -1,       1, 1,
		   0,  0,  1,       0,  0, -1,       1, 0,
		   0,  1,  1,       0,  0, -1,       0, 0,
           1,  1,  1,       0,  0, -1,       0, 1,
          // Right v2,v3,v4,v5
           1,  1,  0,       1,  0,  0,       1, 1,
           1,  1,  1,       1,  0,  0,       1, 0,
           1,  0,  1,       1,  0,  0,       0, 0,
           1,  0,  0,       1,  0,  0,       0, 1,
		  // Left v0,v1,v6,v7	
		   0,  0,  0,      -1,  0,  0,       1, 1,
		   0,  1,  0,      -1,  0,  0,       1, 0,
		   0,  1,  1,      -1,  0,  0,       0, 0,
		   0,  0,  1,      -1,  0,  0,       0, 1,
          // Top v1,v2,v5,v6	
           0,  1,  0,       0,  1,  0,       1, 1,
           1,  1,  0,       0,  1,  0,       1, 0,
           1,  1,  1,       0,  1,  0,       0, 0,
           0,  1,  1,       0,  1,  0,       0, 1,
          // Bottom v0,v7,v4,v3
           0,  0,  0,       0, -1,  0,       1, 1,
		   0,  0,  1,       0, -1,  0,       1, 0,
		   1,  0,  1,       0, -1,  0,		 0, 0,
           1,  0,  0,       0, -1,  0,       0, 1
           
           

    };

    const unsigned int CubeData::indices[] = {
	   	   0, 1, 2,   2, 3, 0,      // front
		   4, 5, 6,   6, 7, 4,      // back
		   8, 9,10,  10,11, 8,      // right
		  12,13,14,  14,15,12,      // left
		  16,17,18,  18,19,16,      // top
		  20,21,22,  22,23,20		// bottom
    };


    Cube::Cube(const glm::ivec3& position, const short& scale, const glm::vec3& color, const CubeType& cubetype,
		const std::vector<Texture*>& textures)
        : m_position(position), m_textures(textures), m_scale(scale), m_color(color), m_type(cubetype)
    {
		m_textures.reserve(6);
	}

    Cube::~Cube()
    {}


	bool Cube::operator==(const form::Cube& a) {
		if (m_position == a.m_position) {
			return true;
		}
		else {
			return false;
		}
	}
}
