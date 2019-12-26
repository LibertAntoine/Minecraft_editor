#include "Texture.h"
#include "stb_image/stb_image.h"

void Texture::EmptyTextureUI() 
{
  GLCall(glGenTextures(1, &m_TextureID));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

  // TODO: may cause problems...
  /*
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  */

  // TODO: values to be taken from the actual window size
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, 1440, 960, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, 0));
  //GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1080, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}

void Texture::EmptyTextureF() 
{
  GLCall(glGenTextures(1, &m_TextureID));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

  // TODO: may cause problems...
  /*
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  */

  // TODO: values to be taken from the actual window size
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1440, 960, 0, GL_RGBA, GL_FLOAT, 0));
  //GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1080, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
void Texture::EmptyTextureI() 
{
  GLCall(glGenTextures(1, &m_TextureID));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

  // TODO: may cause problems...
  /*
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  */

  // TODO: values to be taken from the actual window size
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32I, 1440, 960, 0, GL_RGBA_INTEGER, GL_INT, 0));
  //GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1080, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
//Texture::Texture()
//    :m_LocalBuffer(nullptr)
//{}

Texture::Texture(const std::string& path, const std::string& name)
	: m_FilePath(path), m_Name(name),
	m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1); //Retourne verticlement la texture.
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));


	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() { GLCall(glDeleteTextures(1, &m_TextureID)); }

void Texture::Bind(unsigned int slot /*= 0*/) const {
  GLCall(glActiveTexture(
      GL_TEXTURE0 +
      slot)); // Selectionne un slot pour la texture, on peut active plusieurs
              // texture dans diff�rent slot, 0 �tant le plus proche.
  // Go � la d�finition de GL_TEXTURE0 pour voir combien notre GPU poss�de de
  // slot.
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::SimpleBind() const {
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Unbind() const { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); }
