#pragma once

/* Utilisation des buffers (variables dans le GPU) */
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer(); //Destructeur.

	void Bind() const;
	void Unbind() const;
};