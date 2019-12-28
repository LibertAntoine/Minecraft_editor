#include "CubeRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "forms/Cube.h"

namespace renderer {
CubeRenderer::CubeRenderer()
{
  form::CubeData cubeData;

  m_ShaderTexture = std::make_unique<Shader>("res/shaders/3D.shader");
  m_ShaderColor = std::make_unique<Shader>("res/shaders/3Dcolor.shader");
  m_ShaderMultiTexture = std::make_unique<Shader>("res/shaders/3Dmultitexture.shader");
  m_ShaderGeometry = std::make_unique<Shader>("res/shaders/Cube.shader");

  m_VAO = std::make_unique<VertexArray>();
  m_VertexBuffer = std::make_unique<VertexBuffer>(cubeData.datas, 6 * 4 * 8 * sizeof(int));

  m_VertexBufferPosition = std::make_unique<VertexBuffer>(nullptr, 0);
  this->updatePosition();

  m_VertexBufferColor = std::make_unique<VertexBuffer>(nullptr, 0);
  this->updateColor();

  m_VertexBufferTexture = std::make_unique<VertexBuffer>(nullptr, 0);
  this->updateTexture();

  m_VertexBufferType = std::make_unique<VertexBuffer>(nullptr, 0);
  this->updateType();

  VertexBufferLayout layout;
  layout.Push<int>(3);
  layout.Push<int>(3);
  layout.Push<int>(2);
  
  VertexBufferLayout layoutPosition;
  layoutPosition.Push<int>(3);

  VertexBufferLayout layoutColor;
  layoutColor.Push<float>(3);

  VertexBufferLayout layoutTexture;
  layoutTexture.Push<unsigned int>(3);
  layoutTexture.Push<unsigned int>(3);

  VertexBufferLayout layoutType;
  layoutType.Push<int>(1);
  
  
  m_VAO->AddBuffer(*m_VertexBuffer, layout);
 
  m_IndexBuffer = std::make_unique<IndexBuffer>(cubeData.indices, 6 * 6);

  m_VAO->AddBuffer(*m_VertexBufferColor, layoutColor, 3, 1);
  m_VAO->AddBuffer(*m_VertexBufferTexture, layoutTexture, 5, 1);
  m_VAO->AddBuffer(*m_VertexBufferPosition, layoutPosition, 4, 1);
  m_VAO->AddBuffer(*m_VertexBufferType, layoutType, 7, 1, 2);

  m_ShaderTexture->Bind();
  m_ShaderTexture->SetUniform1i("uTex", 0);

}

CubeRenderer::~CubeRenderer() {}

form::Cube *CubeRenderer::add(const form::Cube& cube)
{
  m_CubeList.push_back(cube);
    this->updatePosition();
    this->updateColor();
    this->updateTexture();
    this->updateType();
  return &m_CubeList.back();
}

void CubeRenderer::del(form::Cube* cube) { 
    m_CubeList.remove(*cube);
    this->updatePosition();
    this->updateColor();
    this->updateTexture();
    this->updateType();
}

void CubeRenderer::draw(glm::mat4 view, glm::mat4 projection, interaction::LightManager& lightManager, const TextureArray& texture)
{
  Renderer renderer;
  
  glm::mat4 MVMatrix = view;
  MVMatrix = glm::scale(MVMatrix, glm::vec3(2, 2, 2));
  glActiveTexture(GL_TEXTURE0);
  m_ShaderGeometry->Bind();
  m_ShaderGeometry->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
  m_ShaderGeometry->Bind();
  texture.Bind();
  m_VAO->Bind();
  GLCall(glDrawElementsInstanced(GL_POINTS, 6 * 4 * 8 * sizeof(int) + sizeof(glm::ivec3) + sizeof(glm::vec3) + 7 * sizeof(unsigned int) , GL_UNSIGNED_INT, 0, m_CubeList.size()));
  
}

void CubeRenderer::drawSelector(const glm::vec3 &position, const int &scale,
                                std::shared_ptr<Texture> texture,
                                glm::mat4 view, glm::mat4 projection)
{
  Renderer renderer;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH_TEST);

  texture->Bind();
  glm::mat4 MVMatrix = glm::translate(
      glm::mat4(1.0f), position + glm::vec3(-0.015, -0.015, -0.015));
  MVMatrix =
      glm::scale(MVMatrix, glm::vec3(scale + 0.03, scale + 0.03, scale + 0.03));
  glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  MVMatrix = view * MVMatrix;
  m_ShaderTexture->Bind();
  GLCall(glLineWidth(5));

  m_ShaderTexture->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
  m_ShaderTexture->SetUniformMat4f("uMVMatrix", MVMatrix);
  m_ShaderTexture->SetUniformMat4f("uNormalMatrix", NormalMatrix);

  renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_ShaderTexture);
  glEnable(GL_DEPTH_TEST);
  texture->Bind();
};




    void CubeRenderer::updatePosition() {
        std::vector<glm::ivec3> positions;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&positions](form::Cube& cube) {
            positions.push_back(cube.position());
        });
        m_VertexBufferPosition->Update(positions.data(), sizeof(glm::ivec3) * positions.size());
    }

    void CubeRenderer::updateColor() {
        std::vector<glm::vec3> colors;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&colors](form::Cube& cube) {
            colors.push_back(cube.color());
        });
        m_VertexBufferColor->Update(colors.data(), sizeof(glm::vec3) * colors.size());
    }

    void CubeRenderer::updateTexture() {
        std::vector<unsigned int> textures;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&textures](form::Cube& cube) {
            textures.push_back(cube.texture()[0]);
            textures.push_back(cube.texture()[1]);
            textures.push_back(cube.texture()[2]);
            textures.push_back(cube.texture()[3]);
            textures.push_back(cube.texture()[4]);
            textures.push_back(cube.texture()[5]);
            
        });
        m_VertexBufferTexture->Update(textures.data(), 6 * sizeof(unsigned int) * textures.size());
    }

    void CubeRenderer::updateType() {
        std::vector<int> types;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&types](form::Cube& cube) {
            types.push_back(cube.type());
        });
        m_VertexBufferType->Update(types.data(), sizeof(int) * types.size());
    }
} // namespace renderer
