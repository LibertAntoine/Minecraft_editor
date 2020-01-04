#pragma once

/**
 * \file GLerror.h
 * \brief Manage the OpenGL render commands.
 * \author Antoine Libert & Nicolas Lienart
 * Launch the different render type command with error repport.
 * Manage the bind of VAO, buffer and shader for each.
 */

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
  public:

	/**
	* \brief Clear the color buffer.
	*/
    void Clear() const;


    void Draw(const GLenum& type, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawNoIndexBuffer(const GLenum& type, const VertexArray& va, const Shader& shader, const int &count) const;
};
