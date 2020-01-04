#pragma once


#include <glm/glm.hpp>
#include "GraphicEngine/Texture.h"
#include <vector>

namespace Forms {

  typedef enum CubeType {
    COLORED = 0,
    TEXTURED = 1,
    MULTI_TEXTURED = 2
  } CubeType;


  typedef struct CubeData {
    static const int datas[];
    static const unsigned int indices[];
  } CubeData;

  class Cube {
    public:
      Cube(const glm::ivec3& position = glm::ivec3(0, 0, 0), const short& scale = 3,
          const glm::vec3 & color = glm::vec3(0.5f, 0.5f, 0.5f), const CubeType & cubetype = COLORED,
          const std::vector<unsigned int>& textures = {0,0,0,0,0,0}
          );
      ~Cube();

        bool operator==(const Forms::Cube& a);

      inline const glm::ivec3& position() const { return m_position; };
      inline glm::ivec3& position() { return m_position; };
      inline void position(const glm::ivec3& position) { m_position = position; };
      inline std::vector<unsigned int>& texture() { return m_textures; };
      inline int& scale() { return m_scale; };
      inline int* scalePtr() { return &m_scale; };
      inline glm::vec3& color() { return m_color; };
      inline void Setcolor(const glm::vec3& color) { m_color = color; };
      inline CubeType& type() { return m_type; };


    public:
      static const int datas[];
      static const unsigned int indices[];

    private:
      glm::ivec3 m_position;
      std::vector<unsigned int> m_textures;
      int m_scale;
      glm::vec3 m_color;
      CubeType m_type;
  };
}
