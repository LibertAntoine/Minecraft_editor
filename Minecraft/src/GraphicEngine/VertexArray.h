#pragma once

/**
 * \file VertexArray.h
 * \brief Manage a VertexArray
 * \author Antoine Libert & Nicolas Lienart
 */

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private: 
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	/**
	* \brief Init a Vertex Array.
	* \param vb vextexBuffer to add in the array
	* \param layout corresping to the vertexBuffer.
	* \param place where begin the layout addition in the array (if already present layout, it will be replaced).
	* \param divisor if instancing draw, number of instance between each layout switch.
	* \param flat put false if it is flat data in the shader.
	*/
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const int& place = 0, const int& divisor = 0, const bool& flat = 1);
	
	/**
	* \brief Bind the Vertex Array.
	*/
	void Bind() const;

	/**
	* \brief Unbind the Vertex Array.
	*/
	void Unbind() const;
};
