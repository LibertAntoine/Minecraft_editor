#pragma once


#include <glm/glm.hpp>
#include "Texture.h"
#include <vector>

namespace form {

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
          const std::vector<Texture*>& textures = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
          );
      ~Cube();

      bool operator==(const form::Cube a);

      inline const glm::ivec3& position() const { return m_position; };
      inline glm::ivec3& position() { return m_position; };
      inline void position(const glm::ivec3& position) { m_position = position; };
      inline std::vector<Texture*>& texture() { return m_textures; };
      inline int& scale() { return m_scale; };
      inline int* scalePtr() { return &m_scale; };
      inline const glm::vec3 color() const { return m_color; };
      inline void Setcolor(const glm::vec3& color) { m_color = color; };
      inline CubeType& type() { return m_type; };


    public:
      static const int datas[];
      static const unsigned int indices[];

    private:
      glm::ivec3 m_position;
      std::vector<Texture*> m_textures;
      int m_scale;
      glm::vec3 m_color;
      CubeType m_type;
  };
}

