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

  // NOTE: switched from unsigned int to GLfloat because the shader was already handling floats (standard vec(i) data type)
	const GLfloat CubeData::datas[] = {
        // Front v0,v1,v2,v3
           0.f,  0.f,  0.f,       0.f,  0.f,  1.f,       0.f,  1.f,  1.f,
           0.f,  1.f,  0.f,       0.f,  0.f,  1.f,       1.f,  1.f,  1.f,
           1.f,  1.f,  0.f,       0.f,  0.f,  1.f,       1.f,  0.f,  1.f,
           1.f,  0.f,  0.f,       0.f,  0.f,  1.f,       0.f,  0.f,  1.f,
         // Right v2,v3,v4,v5
           1.f,  1.f,  0.f,       1.f,  0.f,  0.f,       1.f,  1.f,  2.f,
           1.f,  1.f,  1.f,       1.f,  0.f,  0.f,       1.f,  0.f,  2.f,
           1.f,  0.f,  1.f,       1.f,  0.f,  0.f,       0.f,  0.f,  2.f,
           1.f,  0.f,  0.f,       1.f,  0.f,  0.f,       0.f,  1.f,  2.f,
          // Top v1,v2,v5,v6	
           0.f,  1.f,  0.f,       0.f,  1.f,  0.f,       1.f,  1.f,  3.f,
           1.f,  1.f,  0.f,       0.f,  1.f,  0.f,       0.f,  1.f,  3.f,
           1.f,  1.f,  1.f,       0.f,  1.f,  0.f,       0.f,  0.f,  3.f,
           0.f,  1.f,  1.f,       0.f,  1.f,  0.f,       1.f,  0.f,  3.f,
          // Left v0,v1,v6,v7	
           0.f,  0.f,  0.f,       -1.f,  0.f,  0.f,       0.f,  1.f,  4.f,
           0.f,  1.f,  0.f,       -1.f,  0.f,  0.f,       1.f,  1.f,  4.f,
           0.f,  1.f,  1.f,       -1.f,  0.f,  0.f,       1.f,  0.f,  4.f,
           0.f,  0.f,  1.f,       -1.f,  0.f,  0.f,       0.f,  0.f,  4.f,
          // Bottom v0,v3,v4,v7
           0.f,  0.f,  0.f,       0.f,  -1.f,  0.f,       0.f,  1.f,  5.f,
           1.f,  0.f,  0.f,       0.f,  -1.f,  0.f,       1.f,  1.f,  5.f,
           1.f,  0.f,  1.f,       0.f,  -1.f,  0.f,       1.f,  0.f,  5.f,
           0.f,  0.f,  1.f,       0.f,  -1.f,  0.f,       0.f,  0.f,  5.f,
          // Back v4,v5,v6,v7	
           1.f,  0.f,  1.f,       0.f,  0.f,  -1.f,       1.f,  0.f,  6.f,
           1.f,  1.f,  1.f,       0.f,  0.f,  -1.f,       0.f,  0.f,  6.f,
           0.f,  1.f,  1.f,       0.f,  0.f,  -1.f,       0.f,  1.f,  6.f,
           0.f,  0.f,  1.f,       0.f,  0.f,  -1.f,        1.f,  1.f,  6.f
    };

    const unsigned int CubeData::indices[] = {
	   	   0, 1, 2,   2, 3, 0,      // front
		   4, 5, 6,   6, 7, 4,      // right
		   8, 9,10,  10,11, 8,      // top
		  12,13,14,  14,15,12,      // left
		  16,17,18,  18,19,16,      // bottom
		  20,21,22,  22,23,20		// back
    };


    Cube::Cube(const glm::vec3& position, Texture* texture, const short& scale, const glm::vec3& color)
        : m_position(position), m_texture(texture), m_scale(scale), m_color(color)
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
