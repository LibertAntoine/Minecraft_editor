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
  m_ShaderGeometry = std::make_unique<Shader>("res/shaders/testGeometrie.shader");

  m_VAO = std::make_unique<VertexArray>();
  m_VertexBuffer =
      std::make_unique<VertexBuffer>(cubeData.datas, 6 * 4 * 8 * sizeof(int));


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
  layoutType.Push<unsigned int>(1);
  
  
  m_VAO->AddBuffer(*m_VertexBuffer, layout);
 
  m_IndexBuffer = std::make_unique<IndexBuffer>(cubeData.indices, 6 * 6);

  m_VAO->AddBuffer(*m_VertexBufferColor, layoutColor, 3, 1);
  m_VAO->AddBuffer(*m_VertexBufferTexture, layoutTexture, 5, 1);
  m_VAO->AddBuffer(*m_VertexBufferPosition, layoutPosition, 4, 1);
  m_VAO->AddBuffer(*m_VertexBufferType, layoutType, 7, 1);
 
  

  m_ShaderMultiTexture->Bind();
  m_ShaderMultiTexture->SetUniform1i("uTexture1", 0);
  m_ShaderMultiTexture->SetUniform1i("uTexture2", 1);
  m_ShaderMultiTexture->SetUniform1i("uTexture3", 2);
  m_ShaderMultiTexture->SetUniform1i("uTexture4", 3);
  m_ShaderMultiTexture->SetUniform1i("uTexture5", 4);
  m_ShaderMultiTexture->SetUniform1i("uTexture6", 5);

}

CubeRenderer::~CubeRenderer() {}

form::Cube *CubeRenderer::add(const form::Cube &cube)
{
  m_CubeList.push_back(cube);
    this->updatePosition();
    this->updateColor();
    this->updateTexture();
    this->updateType();
  return &m_CubeList.back();
}

void CubeRenderer::del(form::Cube *cube) { 
    /*m_CubeList.remove(*cube);*/ 
    this->updatePosition();
    this->updateColor();
    this->updateTexture();
    this->updateType();
}

void CubeRenderer::draw(glm::mat4 view, glm::mat4 projection, interaction::LightManager& lightManager, const TextureArray& texture)
{
  Renderer renderer;
  
  glm::mat4 MVMatrix = view;
  glActiveTexture(GL_TEXTURE0);
  m_ShaderGeometry->Bind();
  m_ShaderGeometry->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
  m_ShaderGeometry->Bind();
  texture.Bind();
  m_VAO->Bind(); // Fait le lien avec le vertex buffer
  //GLCall(glDrawArrays(GL_POINTS, 0, m_CubeList.size()));
  GLCall(glDrawElementsInstanced(GL_POINTS, 6 * 4 * 8 * sizeof(int) + sizeof(glm::ivec3) + sizeof(glm::vec3) + 7 * sizeof(unsigned int) , GL_UNSIGNED_INT, 0, m_CubeList.size()));
  
  /*
  std::for_each(
      m_CubeList.begin(), m_CubeList.end(),
      [this, &renderer, &view, &projection, &lightManager,&texture](form::Cube &cube) {
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3)cube.position());
        MVMatrix = glm::scale(
            MVMatrix, glm::vec3(cube.scale(), cube.scale(), cube.scale()));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVMatrix = view * MVMatrix;

        if (cube.type() == form::COLORED) {
			m_ShaderColor->Bind();
			m_ShaderColor->SetUniform3f("uColor", cube.color().x, cube.color().y,
				cube.color().z);
			m_ShaderColor->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_ShaderColor->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_ShaderColor->SetUniformMat4f("uNormalMatrix", NormalMatrix);
			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_ShaderColor);
			//m_ShaderColor->Unbind();

        } else if(cube.type() == form::TEXTURED) {

			if (cube.texture()[0] == nullptr)
				assert("[CubeRenderer] No Main Texture to render");
			cube.texture()[0]->Bind();
			m_ShaderTexture->Bind();
			m_ShaderTexture->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_ShaderTexture->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_ShaderTexture->SetUniformMat4f("uNormalMatrix", NormalMatrix);
			m_ShaderTexture->SetUniform3f("uKd", lightManager.dirLight().uKd.x, lightManager.dirLight().uKd.y, lightManager.dirLight().uKd.z);
			m_ShaderTexture->SetUniform3f("uKs", lightManager.dirLight().uKs.x, lightManager.dirLight().uKs.y, lightManager.dirLight().uKs.z);
			m_ShaderTexture->SetUniform3f("uLightDir_vs", lightManager.dirLight().lightDirection.x, lightManager.dirLight().lightDirection.y, lightManager.dirLight().lightDirection.z);
			m_ShaderTexture->SetUniform3f("uLightIntensity", lightManager.dirLight().lightIntensity.x, lightManager.dirLight().lightIntensity.y, lightManager.dirLight().lightIntensity.z);
			m_ShaderTexture->SetUniform1f("uShininess", lightManager.dirLight().shininess);
            glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_ShaderTexture);
			cube.texture()[0]->Bind();
			//m_ShaderTexture->Unbind();
		} else if (cube.type() == form::MULTI_TEXTURED) {

			if (cube.texture()[0] == nullptr)
				assert("[CubeRenderer] No Main Texture to render");
			m_ShaderMultiTexture->Bind();
			cube.texture()[0]->Bind(0);
			cube.texture()[1]->Bind(1);
			cube.texture()[2]->Bind(2);
			cube.texture()[3]->Bind(3);
			cube.texture()[4]->Bind(4);
			cube.texture()[5]->Bind(5);
			
			m_ShaderMultiTexture->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_ShaderMultiTexture->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_ShaderMultiTexture->SetUniformMat4f("uNormalMatrix", NormalMatrix);
			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_ShaderMultiTexture);
			cube.texture()[0]->Unbind();
		}
      });
      */
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
        std::vector<unsigned int> types;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&types](form::Cube& cube) {
            types.push_back(cube.type());
        });
        m_VertexBufferType->Update(types.data(), sizeof(unsigned int) * types.size());
    }
} // namespace renderer
