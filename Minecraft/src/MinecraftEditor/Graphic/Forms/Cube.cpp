#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Forms {

    Cube::Cube(const glm::ivec3& position, const short& scale, const glm::vec3& color, const CubeType& cubetype,
		const std::vector<unsigned int>& textures)
        : m_position(position), m_textures(textures), m_scale(scale), m_color(color), m_type(cubetype)
    {}

    Cube::~Cube()
    {}

	bool Cube::operator==(const Forms::Cube& a) {
		if (m_position == a.m_position) {
			return true;
		}
		else {
			return false;
		}
	}
}

