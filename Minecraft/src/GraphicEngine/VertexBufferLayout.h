#pragma once

/**
 * \file VertexArray.h
 * \brief Manage a Vertex Buffer Layout
 * \author Antoine Libert & Nicolas Lienart
 */

#include <vector>
#include <GL/glew.h>
#include "GLerror.h"

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

 /**
 * \brief Return the number of byte corresponding to the type gived.
 * \param type Glenum which we want the number of byte.
 * \return number of byte which correspond to the type.
 */
  static unsigned int GetSizeOfType(GLenum type)
  {
    switch (type)
    {
      case GL_FLOAT:			
        return 4;
      case GL_UNSIGNED_INT:
        return 4;
      case GL_INT:
        return 4;
      case GL_UNSIGNED_BYTE:
        return 1;
    }
    ASSERT(false);
    return 0;
  }
};

namespace details {
	/**
	* \brief Give the Glenum which correspond of the typename currently push.
	* \return the GLenum corresponding.
	*/
  template<typename T>
    GLenum getGLenum();

	/**
	* \brief Return a GL_TRUE for a typename char.
	* \return the GLbool corresponding.
	*/
  template<typename T>
    unsigned char getGLbool();
}

class VertexBufferLayout
{
  private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
  public:
    VertexBufferLayout()
      : m_Stride(0) {};

	/**
	* \brief Push a new layout element.
	* \param count number of primary element in the layout
	* \note typename T correspond to the primary element type in the layout.
	*/
    template<typename T>
      void Push(unsigned int count)
      {
        m_Elements.push_back({ details::getGLenum<T>(), count, details::getGLbool<T>()});
        m_Stride += count * VertexBufferElement::GetSizeOfType(details::getGLenum<T>());
      }

	// GETTERS - SETTERS //
    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};
