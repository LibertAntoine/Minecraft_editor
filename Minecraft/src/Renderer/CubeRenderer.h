#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include <list>
#include "forms/Cube.h"
#include "Interaction/LightManager.h"
#include "TextureArray.h"

namespace renderer {

  class CubeRenderer 
  {
    private:
      std::unique_ptr<VertexArray> m_VAO;
      std::unique_ptr<VertexBuffer> m_VertexBufferPosition;
      std::unique_ptr<VertexBuffer> m_VertexBufferColor;
      std::unique_ptr<VertexBuffer> m_VertexBufferTexture;
      std::unique_ptr<VertexBuffer> m_VertexBufferType;

      std::unique_ptr<Shader> m_ShaderSelector;
	  std::unique_ptr<Shader> m_ShaderCube;
      std::unique_ptr<Shader> m_ShaderCubeDirLight;
      std::unique_ptr<Shader> m_ShaderCubePonctLight;

    public:
      std::list<form::Cube> m_CubeList;
      CubeRenderer();
      ~CubeRenderer();
      form::Cube* add(const form::Cube& cube);

      void updatePosition();
      void updateColor();
      void updateTexture();
      void updateType();

      void del(form::Cube* cube);
      void draw(glm::mat4 view, glm::mat4 projection, interaction::LightManager& lightManager, const TextureArray& texture);
      void drawSelector(const glm::vec3& position, const int& scale, std::shared_ptr<Texture> texture, glm::mat4 view, glm::mat4 projection);
  };

}
