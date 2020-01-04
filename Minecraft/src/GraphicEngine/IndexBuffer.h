#pragma once


/**
 * \file IndexBuffer.h
 * Manage the OpenGL IndexBuffer
 * \author Antoine Libert & Nicolas Lienart
 * Encapsulate the IndexBuffer logic
 * Can Give the Buffer Renderer ID et return the potential Error.
 */

class IndexBuffer
{
private:
	unsigned int m_RendererID;

	// Number of data in the buffer //
	unsigned int m_Count;
public:

	/**
	* \brief Construct a new IndexBuffer
	* \param data Pointer on the data to put in the IndexBuffer.
	* \param count Number of unsigned int in the Index Buffer.
	*/
	IndexBuffer(const unsigned int* data, unsigned int count); 
	~IndexBuffer(); 

	/**
	* \brief Bind the Index Buffer
	*/
	void Bind() const;

	/**
	* \brief Unbind the Index Buffer
	*/
	void Unbind() const;

	// GETTERS - SETTERS //
	inline unsigned int GetCount() const { return m_Count; }
};