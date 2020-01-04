#pragma once

/**
 * \file Cube.h
 * \brief Contains data relative to a cube of the scene.
 * \author Antoine Libert & Nicolas Lienart
 */


#include <glm/glm.hpp>
#include "GraphicEngine/Texture.h"
#include <vector>

namespace Forms {

  /**
  * \brief determine if the cube will be designed with color, texture or multi-texture.
  */
  typedef enum CubeType {
    COLORED = 0,
    TEXTURED = 1,
    MULTI_TEXTURED = 2
  } CubeType;

  class Cube {
    public:

	  /**
	  * \brief Create a new cube
      * \param Position of the cube in the scene.
	  * \param Scale of the cube.
	  * \param Color of the cube in RGB.
	  * \param Type of the cube (COLORED|TEXTURED|MULTI_TEXTURED)
	  * \param Texture for each face of the cube (the first is the texture by default).
	  */
      Cube(const glm::ivec3& position = glm::ivec3(0, 0, 0), const short& scale = 3,
          const glm::vec3 & color = glm::vec3(0.5f, 0.5f, 0.5f), const CubeType & cubetype = COLORED,
          const std::vector<unsigned int>& textures = {0,0,0,0,0,0}
          );
      ~Cube();
	  /**
	  * \brief Compare position of the two Cubes.
      * \param Cube to compare
      */
      bool operator==(const Forms::Cube& a);

	  // GETTERS - SETTERS //
      inline const glm::ivec3& position() const { return m_position; };
      inline glm::ivec3& position() { return m_position; };
      inline void position(const glm::ivec3& position) { m_position = position; };
      inline std::vector<unsigned int>& texture() { return m_textures; };
      inline int& scale() { return m_scale; };
      inline int* scalePtr() { return &m_scale; };
      inline glm::vec3& color() { return m_color; };
      inline void Setcolor(const glm::vec3& color) { m_color = color; };
      inline CubeType& type() { return m_type; };

    private:
      glm::ivec3 m_position;
      std::vector<unsigned int> m_textures;
      int m_scale;
      glm::vec3 m_color;
      CubeType m_type;
  };
}

