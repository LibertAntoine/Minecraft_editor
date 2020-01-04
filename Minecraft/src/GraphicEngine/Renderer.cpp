#include "Renderer.h"

#include "GLerror.h"
#include <iostream>

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::DrawElements(const GLenum& type, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
  shader.Bind();
  va.Bind(); 
  ib.Bind(); 
  GLCall(glDrawElements(type, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
  ib.Unbind();
  va.Unbind();
  shader.Unbind();
}

void Renderer::DrawArrays(const GLenum& type, const VertexArray& va, const Shader& shader, const int &count) const
{
  shader.Bind();
  va.Bind(); 
  GLCall(glDrawArrays(type, 0, count));
  va.Unbind();
  shader.Unbind();
}


void Renderer::DrawArraysInstanced(const GLenum& type, const VertexArray& va, const Shader& shader, const int& count) const
{
	shader.Bind();
	va.Bind(); 
	GLCall(glDrawArraysInstanced(type, 0, count, count));
	va.Unbind();
	shader.Unbind();
}
