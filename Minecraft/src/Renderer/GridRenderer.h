#pragma once


#include <iostream>
#include <vector>
#include <algorithm>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "forms/Grid.h"
#include <memory>




namespace renderer {
  class GridRenderer
  {
    private:
      std::unique_ptr<VertexArray> m_VAOGrid;
      std::unique_ptr<IndexBuffer> m_IndexBufferGrid;
      std::unique_ptr<VertexBuffer> m_VertexBufferGrid;
      std::unique_ptr<Shader> m_ShaderGrid;
	  form::Grid m_grid;

	  std::unique_ptr<VertexArray> m_VAOGridSelection;
	  std::unique_ptr<VertexBuffer> m_VertexBufferGridSelection;
	  std::unique_ptr<IndexBuffer> m_IndexBufferGridSelection;
	  std::unique_ptr<Shader> m_ShaderGridSelection;
	  form::GridSelection m_gridSelection;

    public:
      GridRenderer(const unsigned int& size, glm::vec3 color);
      ~GridRenderer();
      void draw(const camera::FreeflyCamera& camera, const glm::mat4& projection, bool* active);
	  void drawGridSelection(const camera::FreeflyCamera& camera, const glm::mat4& projection);
  };

}
