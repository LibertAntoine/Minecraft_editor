#pragma once


#include <iostream>
#include <vector>
#include <algorithm>
#include "GraphicEngine/VertexBuffer.h"
#include "GraphicEngine/VertexArray.h"
#include "GraphicEngine/IndexBuffer.h"
#include "GraphicEngine/Shader.h"
#include "GraphicEngine/VertexBufferLayout.h"
#include "GraphicEngine/Camera.h"
#include "MinecraftEditor/Graphic/Forms/Grid.h"
#include <memory>




namespace renderer {
  class GridRenderer
  {
    private:
      std::unique_ptr<VertexArray> m_VAOGrid;
      std::unique_ptr<IndexBuffer> m_IndexBufferGrid;
      std::unique_ptr<VertexBuffer> m_VertexBufferGrid;
      std::unique_ptr<Shader> m_ShaderGrid;
	  Forms::Grid m_grid;

	  std::unique_ptr<VertexArray> m_VAOGridSelection;
	  std::unique_ptr<VertexBuffer> m_VertexBufferGridSelection;
	  std::unique_ptr<IndexBuffer> m_IndexBufferGridSelection;
	  std::unique_ptr<Shader> m_ShaderGridSelection;
	  Forms::GridSelection m_gridSelection;

    public:
      GridRenderer(const unsigned int& size, glm::vec3 color);
      ~GridRenderer();
      void draw(const camera::FreeflyCamera& camera, const glm::mat4& projection, bool* active);
	  void drawGridSelection(const camera::FreeflyCamera& camera, const glm::mat4& projection);
  };

}
