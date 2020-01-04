#pragma once

/**
 * \file Renderer.h
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

	/**
	* \brief Draw Elements in function of the vao, index buffer and shader gived.
	* \param type of drawing (GL_POINT, GL_TRINGLE...)
	* \param va Vextex Array used for the drawing.
	* \param ib Index Buffer used for the drawing.
	* \param shader Shader used for the drawing.
	*/
    void DrawElements(const GLenum& type, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	/**
	* \brief Draw a array of form.
	* \param type of drawing form (GL_POINT, GL_TRINGLE...)
	* \param va Vextex Array used for the drawing.
	* \param number of form to draw.
	*/
    void DrawArrays(const GLenum& type, const VertexArray& va, const Shader& shader, const int &count) const;

	/**
	* \brief Draw a instanced array of form.
	* \param type of drawing form (GL_POINT, GL_TRINGLE...)
	* \param va Vextex Array used for the drawing.
	* \param number of form to draw.
	*/
	void DrawArraysInstanced(const GLenum& type, const VertexArray& va, const Shader& shader, const int& count) const;
};
