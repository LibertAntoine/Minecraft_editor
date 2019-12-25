#include "GroundSelectionRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace renderer {
  GroundSelectionRenderer::GroundSelectionRenderer(const unsigned int& half_size)
    :m_grid(form::Gridv2(half_size))

  {
    m_Shader = std::make_unique<Shader>("res/shaders/GroundSelection.shader");

    m_VAO = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(m_grid.datas().data(), pow( half_size * 2 + 1, 2 ) * 2 * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.Push<GLfloat>(2);

    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(m_grid.indices().data(), m_grid.indices().size());

    //m_Shader->Bind();
    //m_Shader->SetUniform4f("u_Color", color.x, color.y, color.z, 0.3f);

  }


  void GroundSelectionRenderer::draw(const camera::FreeflyCamera& camera, const glm::mat4& projection, bool* active)
  {
    int gridWidth = m_grid.size();

    Renderer renderer;
    GLCall(glLineWidth(1));
    GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT1));
    glClearColor(1, 1, 1, 0); // White for unselectable air
    // TODO: Set dynamic values
    glViewport(0, 0, 1440, 960);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    glm::mat4 MVMatrix;
    int gridMove = round(camera.position().y) - gridWidth /2;

    if (gridMove < 0)
      gridMove = 0;

    // TODO: Clarify active[] role
    // NOTE: gridWidth * 4 == total vertices that constitute the grid

    m_Shader->Bind();
    MVMatrix = glm::mat4(1) * camera.getViewMatrix();
    MVMatrix = glm::rotate(MVMatrix, glm::pi<float>() / 2, glm::vec3(1.f, 0.f, 0.f));
    MVMatrix = glm::translate(MVMatrix, glm::vec3(glm::round(camera.position().x), glm::round(camera.position().y), 0.f));
    glm::mat4 Translation = glm::mat4(1);
    Translation = glm::translate(Translation, glm::vec3(glm::round(camera.position().x), glm::round(camera.position().y), 0.f));
    m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
    m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
    m_Shader->SetUniformMat4f("uTranslation", Translation);
    renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);
    m_Shader->Unbind();
  }

  GroundSelectionRenderer::~GroundSelectionRenderer() {}
}
