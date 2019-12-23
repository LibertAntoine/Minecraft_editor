#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"


struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;
  unsigned char makeFloat;


  VertexBufferElement(unsigned int type, unsigned int count, unsigned int normalized, unsigned int makeFloat)
    :type(type),
    count(count),
    normalized(normalized),
    makeFloat(makeFloat) {}

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_INT:			return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}

};


namespace details {
	template<typename T>
	GLenum getGLenum();

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


	template<typename T, GLboolean normalized = GL_FALSE, GLboolean make_float = GL_TRUE>
	void Push(unsigned int count) {
		m_Elements.push_back(VertexBufferElement( details::getGLenum<T>(), count, normalized, make_float ));
		//m_Elements.push_back({ details::getGLenum<T>(), count, normalized, makeFloat});
		m_Stride += count * VertexBufferElement::GetSizeOfType(details::getGLenum<T>());
	}
	

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};
