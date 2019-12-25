#include "Renderer.h"

#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error] (" << error << "):" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const GLenum& type, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
  //Définit les outils de dessin.
  shader.Bind();
  va.Bind(); // Fait le lien avec le vertex buffer
  ib.Bind(); // Appel de l'index buffer.
  GLCall(glDrawElements(type, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawNoIndexBuffer(const GLenum& type, const VertexArray& va, const Shader& shader, const int &count) const
{
  //Définit les outils de dessin.
  shader.Bind();
  va.Bind(); // Fait le lien avec le vertex buffer
  GLCall(glDrawArrays(type, 0, count));
}
