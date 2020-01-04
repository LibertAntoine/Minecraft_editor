#pragma once

/**
 * \file Texture.h
 * \brief Manage a texture OpenGL element (currently used for proxy images and frame buffer textures).
 * \author Antoine Libert & Nicolas Lienart
 */

#include "App.h"

class Texture
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	std::string m_Name;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public: 

	/**
	* \brief Init an empty texture objet (can used for frameBuffer resulted texture)
	*/
	Texture();

	/**
	* \brief Init a new texture.
	* \param path of the file which contains the texture to load.
	* \param name personalized for the texture menus (name of the file by default).
	*/
	Texture(const std::string& path, const std::string& name = "none");
	~Texture();

    // For selection purposes
	void EmptyTextureUI();
	void EmptyTextureF();
	void EmptyTextureI();

	/**
	* \brief Bind the Texture in the slot specified.
	* \param slot of the texture binded (Slot 0 by default)
	*/
	void Bind(unsigned int slot = 0) const;
        
	/**
	* \brief Unbind the texture.
	*/
	void Unbind() const;

	// GETTERS - SETTERS //
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetTexId() const { return m_TextureID; }
	inline unsigned char* GetData() const { return m_LocalBuffer; }
	inline std::string name() { return m_Name; }
	inline void SetName(const std::string& name) { m_Name = name; }
    inline unsigned int GetTextureID() const { return m_TextureID; }
};
