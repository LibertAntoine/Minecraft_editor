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

    GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
    glClearColor(1, 1, 1, 0); // White for unselectable air
    // TODO: Set dynamic values
    glViewport(0, 0, 1440, 960);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_Shader->Bind();
    std::for_each(cubeList.begin(), cubeList.end(), [&vector_cube_index, this, &renderer, &view, &projection](form::Cube& cube) {
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3)cube.position());
        MVMatrix = view * MVMatrix;

        m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
        m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);

        GLuint idPart[2];

        idPart[0] = (intptr_t(&cube) & 0xFFFFFFFF00000000) >> 32;
        idPart[1] = (intptr_t(&cube) & 0xFFFFFFFF);

        //GLuint test = 0xFFFFFFFF00000000 >> 32;
        m_Shader->SetUniform1uiv("uCubeID", idPart, 2);

        renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);

        /*
        if ( vector_cube_index == 0 ) {
          std::cout << "pointer="<< std::dec << &cube << std::endl;
          std::cout << "color: "<< idPart[0] << ", " << idPart[1] << std::endl;
          std::cout << std::hex << (intptr_t(idPart[0])<<32|idPart[1]) << std::endl;
        }
        */

        vector_cube_index++;
        });
    m_Shader->Unbind();
  }

}
