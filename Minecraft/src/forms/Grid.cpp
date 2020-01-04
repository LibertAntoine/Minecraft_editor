#include "Grid.h"

namespace form {

  Grid::Grid(const int& size, const glm::vec3& color)
    : m_size(size), m_color(color)
  {
    for (int i = -size; i <= size; ++i) {
      m_datas.push_back(i);
      m_datas.push_back(size);
      m_datas.push_back(0);
      m_datas.push_back(i);
      m_datas.push_back(-size);
      m_datas.push_back(0);
    }

    for (int i = -size; i <= size; ++i) {
      m_datas.push_back(size);
      m_datas.push_back(i);
      m_datas.push_back(0);
      m_datas.push_back(-size);
      m_datas.push_back(i);
      m_datas.push_back(0);
    }

    for (int i = 0; i <= size * 8 * 2; i += 2) {
      m_indices.push_back(i);
      m_indices.push_back(i+1);
    }
  }

  Grid::~Grid()
  {}



  // NOTE: Vertex positions are expressed w/o the z index because the ground is flat and it would be redundant
  GridSelection::GridSelection(const int& half_size, const glm::vec3& color)
	  :m_color(color),
	  m_size(half_size * 2)
  {

	  for (int x = -half_size; x <= half_size; x++) {
		  for (int y = -half_size; y <= half_size; y++) {
			  m_datas.push_back(x);
			  m_datas.push_back(y);
		  }
	  }

	  // NOTE: Drawing order in the index buffer
	  //   1,4 - - 5
	  //   | . # # |
	  //   | # . # |
	  //   | # # . |
	  //   0 - - - 2,3
	  //

	  for (int x = 0; x < half_size * 2; x++) {
		  for (int y = 0; y < half_size * 2; y++) {
			  // Lower left square triangle
			  m_indices.push_back((x * (half_size * 2 + 1)) + y);
			  m_indices.push_back((x * (half_size * 2 + 1)) + y + 1);
			  m_indices.push_back((x * (half_size * 2 + 1)) + (half_size * 2 + 1) + y); // Go to next column

			  // Upper right square triangle
			  m_indices.push_back((x * (half_size * 2 + 1)) + (half_size * 2 + 1) + y);
			  m_indices.push_back((x * (half_size * 2 + 1)) + (half_size * 2 + 1) + y + 1);
			  m_indices.push_back((x * (half_size * 2 + 1)) + y + 1);
		  }
	  }

  }
  GridSelection::~GridSelection() {}
}
