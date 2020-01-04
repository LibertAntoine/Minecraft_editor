#pragma once

/**
 * \file TextureArray.h
 * \brief Manage a texture array which contains textures associete to a proxi image texture.
 * \author Antoine Libert & Nicolas Lienart
 */

#include <map>
#include <vector>
#include "Texture.h"

class TextureArray
{
private:
	unsigned int m_TextureArrayID;
	const int m_Width;
	const int m_Height;
	unsigned int m_layerCount;
	unsigned char* m_LocalBuffer;

	// List of the texture in the texture array, the unsigned int correspond to the z position in the texture array.
	std::map<std::string, unsigned int> m_TextureList;
	// List of the proxi image texture for ImGui menu interface.
	std::map<std::string, Texture*> m_ProxiList;
	// Name List of the current texture loaded in the textureArray.
	std::vector<std::string> m_NameList;

public:
	TextureArray() = delete;

	/**
	* \brief Init a new texture array
	* \param witdh of the texture in the array.
	* \param height of the texture in the array.
	*/
	TextureArray(const unsigned int& witdh, const unsigned int& height);
	~TextureArray();

	/**
	* \brief Bind the Texture Array in the slot specified.
	* \param slot of the texture array binded (Slot 0 by default)
	*/
	void Bind(unsigned int slot = 0) const;

	/**
	* \brief Unbind the Texture Array.
	*/
	void Unbind() const;

	/**
	* \brief Add a new texture in the texture array.
	* \param path of the texture file to load in the texture array.
	* \param proxi path of the proxi associate to the texture.
	*/
	void AddTexture(const std::string& path, const std::string& proxi);

	// GETTERS - SETTERS //
	unsigned int give(std::string name);
	Texture* giveProxi(std::string name);
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetTexId() const { return m_TextureArrayID; }
	inline const std::vector<std::string>& nameList() { return m_NameList; };

private:
	/**
	* \brief Recup the name of the texture file.
	* \param path of the texture file.
	* \return the name of the texture file without extension.
	*/
	std::string nammed(const std::string& path);
	/**
	* \brief Add a new proxi to the proxi list
	* \param path of the proxi texture file.
	* \param name of the proxi.
	*/
	void addProxi(const std::string& proxi, const std::string& name);
};

