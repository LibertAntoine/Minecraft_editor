#include "grid.h"

namespace form {

	Grid::Grid(const int& size, const glm::vec3& color)
		: m_size(size), m_color(color)
	{
		for (int i = -size; i < size; ++i) {
			m_datas.push_back(i);
			m_datas.push_back(size);
			m_datas.push_back(0);
			m_datas.push_back(i);
			m_datas.push_back(-size);
			m_datas.push_back(0);
		}

		for (int i = 0; i < size * 4; ++i) {
			m_indices.push_back(i);
			m_indices.push_back(i+1);
		}
	}

	Grid::~Grid()
	{}

}