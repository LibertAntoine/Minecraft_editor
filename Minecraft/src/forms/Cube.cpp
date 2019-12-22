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
        // Front v0,v1,v2,v3
           0,  0,  0,       0,  0,  1,       0, 1,
           0,  1,  0,       0,  0,  1,       1, 1,
           1,  1,  0,       0,  0,  1,       1, 0,
           1,  0,  0,       0,  0,  1,       0, 0,
         // Right v2,v3,v4,v5
           1,  1,  0,       1,  0,  0,       1, 1,
           1,  1,  1,       1,  0,  0,       1, 0,
           1,  0,  1,       1,  0,  0,       0, 0,
           1,  0,  0,       1,  0,  0,       0, 1,
          // Top v1,v2,v5,v6	
           0,  1,  0,       0,  1,  0,       1, 1,
           1,  1,  0,       0,  1,  0,       0, 1,
           1,  1,  1,       0,  1,  0,       0, 0,
           0,  1,  1,       0,  1,  0,       1, 0,
          // Left v0,v1,v6,v7	
           0,  0,  0,      -1,  0,  0,       0, 1,
           0,  1,  0,      -1,  0,  0,       1, 1,
           0,  1,  1,      -1,  0,  0,       1, 0,
           0,  0,  1,      -1,  0,  0,       0, 0,
          // Bottom v0,v3,v4,v7
           0,  0,  0,       0, -1,  0,       0, 1,
           1,  0,  0,       0, -1,  0,       1, 1,
           1,  0,  1,       0, -1,  0,		 1, 0,
           0,  0,  1,       0, -1,  0,       0, 0,
          // Back v4,v5,v6,v7	
           1,  0,  1,       0,  0, -1,       1, 0,
           1,  1,  1,       0,  0, -1,       0, 0,
           0,  1,  1,       0,  0, -1,       0, 1,
           0,  0,  1,       0,  0, -1,       1, 1
    };

    const unsigned int CubeData::indices[] = {
	   	   0, 1, 2,   2, 3, 0,      // front
		   4, 5, 6,   6, 7, 4,      // right
		   8, 9,10,  10,11, 8,      // top
		  12,13,14,  14,15,12,      // left
		  16,17,18,  18,19,16,      // bottom
		  20,21,22,  22,23,20		// back
    };


    Cube::Cube(const glm::ivec3& position, Texture* texture, const short& scale, const glm::vec3& color, const CubeType& cubetype)
        : m_position(position), m_texture(texture), m_scale(scale), m_color(color), m_type(cubetype)
    {}

    Cube::~Cube()
    {}


	bool Cube::operator==(const form::Cube a) {
		if (m_position == a.m_position) {
			return true;
		}
		else {
			return false;
		}
	}
}
