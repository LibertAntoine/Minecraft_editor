#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace form {

	class Grid {
	public:
		Grid() = delete;
		Grid(const int &size, const glm::vec3 &color = glm::vec3(0.5,0.5,0.5));
		~Grid();

		inline const glm::vec3 color() const { return m_color; };
		inline void position(const glm::vec3& color) { m_color = color; };
		inline const unsigned int size() const { return m_size; };


	public:
		static const int datas[];
		static const unsigned int indices[];

	private:
		unsigned int m_size;
		glm::vec3 m_color;
		std::vector<int> m_datas;
		std::vector<unsigned int> m_indices;
	};
}
