#pragma once

#include <iostream>
#include "App.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include <list>
#include <GL/glew.h>
#include "forms/Gridv2.h"
#include "Camera.h"

#include "Shader.h"

namespace renderer {

  class GroundSelectionRenderer
  {
    private:
      std::unique_ptr<VertexArray> m_VAO;
      std::unique_ptr<VertexBuffer> m_VertexBuffer;
      std::unique_ptr<IndexBuffer> m_IndexBuffer;	
      std::unique_ptr<Shader> m_Shader;	
      form::Gridv2 m_grid;



    public:
      GroundSelectionRenderer(const unsigned int &half_size);
      ~GroundSelectionRenderer();
      void draw(const camera::FreeflyCamera& camera, const glm::mat4& projection);
  };
}
