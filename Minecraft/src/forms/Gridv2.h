#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>

namespace form {

  class Gridv2 {
    public:
      Gridv2() = delete;
      Gridv2(const int &half_size, const glm::vec3 &color = glm::vec3(0.5,0.5,0.5));
      ~Gridv2();

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
