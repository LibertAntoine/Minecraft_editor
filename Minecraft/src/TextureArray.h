#pragma once

#include "Renderer.h"
#include <map>
#include "Texture.h"

class TextureArray
{
private:
	unsigned int m_TextureArrayID;
	unsigned int m_layerCount;
	unsigned char* m_LocalBuffer;
	const int m_Width, m_Height;

	std::map<std::string, unsigned int> m_TextureList;
	std::map<std::string, Texture*> m_ProxiList;
	std::vector<std::string> m_NameList;


public:
	TextureArray() = delete;
	TextureArray(const unsigned int& witdh, const unsigned int& height);
	~TextureArray();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void AddTexture(const std::string& path, const std::string& proxi);
	unsigned int give(std::string name);
	Texture* giveProxi(std::string name);

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetTexId() const { return m_TextureArrayID; }
	inline const std::vector<std::string>& nameList() { return m_NameList; };

private:
	std::string nammed(const std::string& path);
	void addProxi(const std::string& proxi, const std::string& name);

};

