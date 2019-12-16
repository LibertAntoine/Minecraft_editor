#include "Grid.h"

namespace form {

	Grid::Grid(const unsigned int& size, const glm::vec3& color)
		: m_size(size), m_color(color)
	{
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				m_datas.push_back(i);
				m_datas.push_back(j);
				m_datas.push_back(0);
			}
		}
	}

	Grid::~Grid()
	{}

}
