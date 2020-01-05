#include "GridRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicEngine/App.h"
#include "GraphicEngine/GLerror.h"


namespace renderer {
  GridRenderer::GridRenderer(const unsigned int& size, glm::vec3 color)
    :m_grid(Forms::Grid(size, color)), m_gridSelection(Forms::GridSelection(size)),
	  m_ShaderGrid(std::make_unique<Shader>("res/shaders/Grid.shader")),
	  m_ShaderGridSelection(std::make_unique<Shader>("res/shaders/GroundSelection.shader")),
	  m_VAOGrid(std::make_unique<VertexArray>()),
	  m_VAOGridSelection(std::make_unique<VertexArray>())
  {
    
    m_VertexBufferGrid = std::make_unique<VertexBuffer>(m_grid.datas().data(), 8.f * (size + 1.0f) * 3.f * sizeof(int));

    VertexBufferLayout layoutGrid;
	layoutGrid.Push<int>(3);

    m_VAOGrid->AddBuffer(*m_VertexBufferGrid, layoutGrid);
    m_IndexBufferGrid = std::make_unique<IndexBuffer>(m_grid.indices().data(), 8 * (size + 1));

    m_ShaderGrid->Bind();
    m_ShaderGrid->SetUniform4f("u_Color", color.x, color.y, color.z, 0.3f);



	m_VertexBufferGridSelection = std::make_unique<VertexBuffer>(m_gridSelection.datas().data(), pow(size * 2 + 1, 2) * 2 * sizeof(GLfloat));

	VertexBufferLayout layoutGridSelection;
	layoutGridSelection.Push<GLfloat>(2);

	m_VAOGridSelection->AddBuffer(*m_VertexBufferGridSelection, layoutGridSelection);
	m_IndexBufferGridSelection = std::make_unique<IndexBuffer>(m_gridSelection.indices().data(), m_gridSelection.indices().size());
  }

  GridRenderer::~GridRenderer() {}

  void GridRenderer::drawGrid(const camera::FreeflyCamera& camera, const glm::mat4& projection, bool* active) {
    Renderer renderer;
    GLCall(glLineWidth(1));
    glm::mat4 MVMatrix;
    int gridMove = round(camera.position().y) - m_grid.size() /2;
    if (gridMove < 0)
      gridMove = 0;

    if (active[1]) {
      MVMatrix = glm::mat4(1) * camera.getViewMatrix();
      MVMatrix = glm::translate(MVMatrix, glm::vec3(round(camera.position().x), gridMove + m_grid.size(), 0.f));
      m_ShaderGrid->Bind();
      m_ShaderGrid->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
      m_ShaderGrid->SetUniformMat4f("uMVMatrix", MVMatrix);
      renderer.DrawElements(GL_LINES, *m_VAOGrid, *m_IndexBufferGrid, *m_ShaderGrid);
    }

    if (active[0]) {
      MVMatrix = glm::mat4(1) * camera.getViewMatrix();
      MVMatrix = glm::rotate(MVMatrix, glm::pi<float>() / 2, glm::vec3(1.f, 0.f, 0.f));
      MVMatrix = glm::translate(MVMatrix, glm::vec3(round(camera.position().x), round(camera.position().y), 0.f));
      m_ShaderGrid->Bind();
      m_ShaderGrid->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
      m_ShaderGrid->SetUniformMat4f("uMVMatrix", MVMatrix);
      renderer.DrawElements(GL_LINES, *m_VAOGrid, *m_IndexBufferGrid, *m_ShaderGrid);
    }
    if (active[2]) {
      MVMatrix = glm::mat4(1) * camera.getViewMatrix();
      MVMatrix = glm::rotate(MVMatrix, glm::pi<float>() / 2, glm::vec3(0.f, 1.f, 0.f));
      MVMatrix = glm::translate(MVMatrix, glm::vec3(round(camera.position().x), gridMove + m_grid.size(), 0.f));
      m_ShaderGrid->Bind();
      m_ShaderGrid->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
      m_ShaderGrid->SetUniformMat4f("uMVMatrix", MVMatrix);
      renderer.DrawElements(GL_LINES, *m_VAOGrid, *m_IndexBufferGrid, *m_ShaderGrid);
    }
  }


  void GridRenderer::drawGridSelection(const camera::FreeflyCamera& camera, const glm::mat4& projection)
  {
	  int gridWidth = m_gridSelection.size();

	  Renderer renderer;
	  GLCall(glLineWidth(1));
	  GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT1));
	  glClearColor(1, 1, 1, 0); // White for unselectable air
	  glViewport(0, 0, App::WINDOW_WIDTH, App::WINDOW_HEIGHT);
	  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	  glm::mat4 MVMatrix;
	  int gridMove = round(camera.position().y) - gridWidth / 2;

	  if (gridMove < 0)
		  gridMove = 0;

	  // NOTE: gridWidth * 4 == total vertices that constitute the grid

	  m_ShaderGridSelection->Bind();
	  MVMatrix = glm::mat4(1) * camera.getViewMatrix();
	  MVMatrix = glm::rotate(MVMatrix, glm::pi<float>() / 2, glm::vec3(1.f, 0.f, 0.f));
	  MVMatrix = glm::translate(MVMatrix, glm::vec3(glm::round(camera.position().x), glm::round(camera.position().y), 0.f));
	  glm::mat4 Translation = glm::mat4(1);
	  Translation = glm::translate(Translation, glm::vec3(glm::round(camera.position().x), glm::round(camera.position().y), 0.f));
	  m_ShaderGridSelection->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
	  m_ShaderGridSelection->SetUniformMat4f("uTranslation", Translation);
	  renderer.DrawElements(GL_TRIANGLES, *m_VAOGridSelection, *m_IndexBufferGridSelection, *m_ShaderGridSelection);
	  m_ShaderGridSelection->Unbind();
  }
}
