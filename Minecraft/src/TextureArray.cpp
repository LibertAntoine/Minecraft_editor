#include "TextureArray.h"
#include "stb_image/stb_image.h"
#include <regex>

TextureArray::TextureArray(const unsigned int& witdh, const unsigned int& height)
    :m_Height(height), m_Width(witdh), m_layerCount(0), m_LocalBuffer(nullptr)
{
    GLCall(glGenTextures(1, &m_TextureArrayID));
    this->Bind();
    GLCall(glTexStorage3D(GL_TEXTURE_2D_ARRAY,
        1,                    // mipmaps
        GL_RGBA8,               //Internal format
        m_Width, m_Height,           //width,height
        100                  //Number of layers
    ));

    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    this->Unbind();
}

void TextureArray::AddTexture(const std::string& path, const std::string& proxi) {
    stbi_set_flip_vertically_on_load(1); //Retourne verticlement la texture.
    int width = 0;
    int height = 0;

    m_LocalBuffer = stbi_load(path.c_str(), &width, &height, nullptr, 4);
    this->Bind();

    if (width <= m_Width && height <= m_Height) {
        GLCall(glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
            0,                      //Mipmap number
            0, 0, m_layerCount, //xoffset, yoffset, zoffset
            m_Width, m_Height, 1,          //width, height, depth
            GL_RGBA,                 //format
            GL_UNSIGNED_BYTE,       //type
            m_LocalBuffer)); //pointer to data
        this->addProxi(proxi, this->nammed(path));
        m_layerCount++;
    } else {
        std::cerr << "Texture " << path << " resolution too high" << std::endl;
    }
    
    this->Unbind();

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}


TextureArray::~TextureArray() { GLCall(glDeleteTextures(1, &m_TextureArrayID)); }

unsigned int TextureArray::give(std::string name) {
    if (m_TextureList.find(name) != m_TextureList.end()) 
        return m_TextureList[name];
    else 
        return 0;
}

Texture* TextureArray::giveProxi(std::string name) {
    if (m_ProxiList.find(name) != m_ProxiList.end()) 
        return m_ProxiList[name];
    else 
        return nullptr;
}



void TextureArray::Bind(unsigned int slot /*= 0*/) const {
    GLCall(glActiveTexture(
        GL_TEXTURE0 +
        slot)); // Selectionne un slot pour la texture, on peut active plusieurs
                // texture dans different slot, 0 etant le plus proche.
    // Go a la definition de GL_TEXTURE0 pour voir combien notre GPU possede de
    // slot.
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureArrayID));
}


void TextureArray::Unbind() const { GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0)); }

std::string TextureArray::nammed(const std::string& path) {
    std::regex name_regex("[a-zA-Z0-9_]*\.png");
    std::smatch name_match;
    if (std::regex_search(path, name_match, name_regex)) {
        std::string name = name_match.str().substr(0, name_match.length() - 4);
        m_TextureList.insert(std::pair<std::string, unsigned int>(name, m_layerCount));
        m_NameList.push_back(name);
        return name;
    }
    else {
        assert("texture has not a png extension");
    }
}

void TextureArray::addProxi(const std::string& proxi, const std::string& name) {
    m_ProxiList.insert(std::pair<std::string, Texture*>(name, new Texture(proxi, name)));
}