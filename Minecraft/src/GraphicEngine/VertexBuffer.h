#pragma once

/**
 * \file VertexArray.h
 * \brief Manage a VertexBuffer
 * \author Antoine Libert & Nicolas Lienart
 */

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:

	/**
	* \brief Init a Vertex Buffer
	* \param data to put in the Vertex Beffer
	* \param size in byte of the VertexBuffer
	*/
	VertexBuffer(const void* data, const unsigned int& size);
	~VertexBuffer(); 

	/**
	* \brief Bind the Vertex Buffer.
	*/
	void Bind() const;

	/**
	* \brief Unbind the Vertex Buffer.
	*/
	void Unbind() const;

	/**
	* \brief upadate the content of the vertex buffer.
	* \param data to put in the Vertex Beffer.
	* \param size in byte of the VertexBuffer.
	*/
	void Update(const void* data, const unsigned int& size) const;
};