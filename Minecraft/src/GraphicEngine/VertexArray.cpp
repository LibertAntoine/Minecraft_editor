#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "GLerror.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const int& place, const int& divisor, const bool& test)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i + place));
		if (test == 0) {
			GLCall(glVertexAttribIPointer(i + place, element.count, element.type, layout.GetStride(), (const void*)(intptr_t)offset));
		}
		else {
			GLCall(glVertexAttribPointer(i + place, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(intptr_t)offset));
		}
		if (divisor > 0) GLCall(glVertexAttribDivisor(i + place, divisor));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
