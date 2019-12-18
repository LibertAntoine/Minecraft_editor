#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>


namespace form {
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3

	const int CubeData::datas[] = {
        // Front v0,v1,v2,v3
           1,  1,  1,       0,  0,  1,       0, 1,
          -1,  1,  1,       0,  0,  1,       1, 1,
          -1, -1,  1,       0,  0,  1,       1, 0,
           1, -1,  1,       0,  0,  1,       0, 0,
         // Right v0,v3,v4,v5
           1,  1,  1,       1,  0,  0,       1, 1,
           1, -1,  1,       1,  0,  0,       1, 0,
           1, -1, -1,       1,  0,  0,       0, 0,
           1,  1, -1,       1,  0,  0,       0, 1,
          // Top v0,v5,v6,v1	
           1,  1,  1,       0,  1,  0,       1, 1,
           1,  1, -1,       0,  1,  0,       0, 1,
          -1,  1, -1,       0,  1,  0,       0, 0,
          -1,  1,  1,       0,  1,  0,       1, 0,
          // Left v1,v6,v7,v2	
          -1,  1,  1,      -1,  0,  0,       0, 1,
          -1,  1, -1,      -1,  0,  0,       1, 1,
          -1, -1, -1,      -1,  0,  0,       1, 0,
          -1, -1,  1,      -1,  0,  0,       0, 0,
          // Bottom v7,v4,v3,v2
          -1, -1, -1,       0, -1,  0,       0, 1,
           1, -1, -1,       0, -1,  0,       1, 1,
           1, -1,  1,       0, -1,  0,		 1, 0,
          -1, -1,  1,       0, -1,  0,       0, 0,
          // Back v4,v7,v6,v5	
           1, -1, -1,       0,  0, -1,       1, 0,
          -1, -1, -1,       0,  0, -1,       0, 0,
          -1,  1, -1,       0,  0, -1,       0, 1,
           1,  1, -1,       0,  0, -1,       1, 1
    };

    const unsigned int CubeData::indices[] = {
	   	   0, 1, 2,   2, 3, 0,      // front
		   4, 5, 6,   6, 7, 4,      // right
		   8, 9,10,  10,11, 8,      // top
		  12,13,14,  14,15,12,      // left
		  16,17,18,  18,19,16,      // bottom
		  20,21,22,  22,23,20		  // back
    };


    Cube::Cube(const glm::vec3& position, const char* texName, const short& scale)
        : m_position(position), m_texture(texName), m_scale(scale)
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
