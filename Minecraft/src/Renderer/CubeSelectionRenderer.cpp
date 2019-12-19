#include "CubeSelectionRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace renderer {
  CubeSelectionRenderer::CubeSelectionRenderer()
    :m_Shader(std::make_unique<Shader>("res/shaders/CubeSelector.shader"))
  {
    form::CubeData cubeData;

    m_VAO = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(cubeData.datas, 6 * 4 * 8 * sizeof(int));

    VertexBufferLayout layout;
    layout.Push<int>(3);
    layout.Push<int>(3);
    layout.Push<int>(2);

    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(cubeData.indices, 6 * 6);

    m_Shader->Bind();
  }

  CubeSelectionRenderer::~CubeSelectionRenderer() {}


  void CubeSelectionRenderer::draw(glm::mat4 view, glm::mat4 projection, std::list<form::Cube>& cubeList)
  {
    Renderer renderer;
    int vector_cube_index = 0;


    m_Shader->Bind();
    std::for_each(cubeList.begin(), cubeList.end(), [&vector_cube_index, this, &renderer, &view, &projection](form::Cube& cube) {
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), cube.position());
        MVMatrix = view * MVMatrix;

        m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
        m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
        m_Shader->SetUniform1i("uCubeID", vector_cube_index);


        renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);

        vector_cube_index++;
        });
    m_Shader->Unbind();
  }

}
