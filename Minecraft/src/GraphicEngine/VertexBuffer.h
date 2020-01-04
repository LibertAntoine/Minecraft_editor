#pragma once

/* Utilisation des buffers (variables dans le GPU) */
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, const unsigned int& size);
	~VertexBuffer(); //Destructeur.

	void Bind() const;
	void Unbind() const;
	void Update(const void* data, const unsigned int& size) const;
};