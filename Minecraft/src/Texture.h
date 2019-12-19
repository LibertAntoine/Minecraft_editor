#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public: 
	Texture();
	Texture(const std::string& path);
	~Texture();


        // For selection purposes
	void EmptyTexture();

	void Bind(unsigned int slot = 0) const;
        
        // NOTE: simple binding
	void SimpleBind() const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

        inline unsigned int GetTextureID() const { return m_TextureID; }
};
