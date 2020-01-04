#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private: 
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const int& place = 0, const int& divisor = 0, int test = 1);
	
	void Bind() const;
	void Unbind() const;
};