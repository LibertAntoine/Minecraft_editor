#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	std::string m_Name;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public: 
	Texture(const std::string& path = "none", const std::string& name = "none");
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

	inline const std::string name() const { return m_Name; }
	inline void SetName(const std::string& name) { m_Name = name; }

        inline unsigned int GetTextureID() const { return m_TextureID; }
};
