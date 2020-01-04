#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>

namespace Forms {

  class Grid {
    public:
      Grid() = delete;
      Grid(const int &size, const glm::vec3 &color = glm::vec3(0.5,0.5,0.5));
      ~Grid();

      inline const glm::vec3 color() const { return m_color; };
      inline void position(const glm::vec3& color) { m_color = color; };
      inline unsigned int size() const { return m_size; };
      inline const std::vector<int> datas() const { return m_datas; };
      inline const std::vector<unsigned int> indices() const { return m_indices; };

    private:
      unsigned int m_size;
      glm::vec3 m_color;
      std::vector<int> m_datas;
      std::vector<unsigned int> m_indices;
  };

  class GridSelection {
  public:
	  GridSelection() = delete;
	  GridSelection(const int& half_size, const glm::vec3& color = glm::vec3(0.5, 0.5, 0.5));
	  ~GridSelection();

	  inline const glm::vec3 color() const { return m_color; };
	  inline const std::vector<GLfloat> datas() const { return m_datas; };
	  inline unsigned int size() const { return m_size; };
	  inline const std::vector<unsigned int> indices() const { return m_indices; };

  private:
	  glm::vec3 m_color;
	  unsigned int m_size;
	  std::vector<GLfloat> m_datas;
	  std::vector<unsigned int> m_indices;
  };
}
