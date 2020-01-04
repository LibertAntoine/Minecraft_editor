#include "CubeRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicEngine/GLerror.h"

namespace renderer {


CubeRenderer::CubeRenderer()
    :m_ShaderCube(std::make_unique<Shader>("res/shaders/Cube.shader")),
    m_ShaderCubeDirLight(std::make_unique<Shader>("res/shaders/CubeDL.shader")),
    m_ShaderCubePonctLight(std::make_unique<Shader>("res/shaders/CubePL.shader")),
    m_ShaderSelector(std::make_unique<Shader>("res/shaders/Selector.shader")),
    m_ShaderClickSelection(std::make_unique<Shader>("res/shaders/CubeSelection.shader")),
    m_VAO(std::make_unique<VertexArray>()),
    m_VertexBufferPosition(std::make_unique<VertexBuffer>(nullptr, 0)),
    m_VertexBufferColor(std::make_unique<VertexBuffer>(nullptr, 0)),
    m_VertexBufferTexture(std::make_unique<VertexBuffer>(nullptr, 0)),
    m_VertexBufferType(std::make_unique<VertexBuffer>(nullptr, 0)),
    m_VertexBufferCubeId(std::make_unique<VertexBuffer>(nullptr, 0))

{
  VertexBufferLayout layoutPosition;
  layoutPosition.Push<int>(3);

  VertexBufferLayout layoutColor;
  layoutColor.Push<float>(3);

  VertexBufferLayout layoutTexture;
  layoutTexture.Push<unsigned int>(3);
  layoutTexture.Push<unsigned int>(3);

  VertexBufferLayout layoutType;
  layoutType.Push<int>(1);

  VertexBufferLayout layoutCubeId;
  layoutCubeId.Push<unsigned int>(2);

  m_VAO->AddBuffer(*m_VertexBufferPosition, layoutPosition, 0, 1);
  m_VAO->AddBuffer(*m_VertexBufferColor, layoutColor, 1, 1);
  m_VAO->AddBuffer(*m_VertexBufferTexture, layoutTexture, 2, 1);
  m_VAO->AddBuffer(*m_VertexBufferType, layoutType, 4, 1, 0);
  m_VAO->AddBuffer(*m_VertexBufferCubeId, layoutCubeId, 5, 1, 0);
}

CubeRenderer::~CubeRenderer() {}

Forms::Cube *CubeRenderer::add(const Forms::Cube& cube)
{
  m_CubeList.push_back(cube);
    this->updatePosition();
    this->updateColor();
    this->updateTexture();
    this->updateType();
    this->updateCubeId();
  return &m_CubeList.back();
}

void CubeRenderer::del(Forms::Cube* cube) { 
    m_CubeList.remove(*cube);
    this->updatePosition();
    this->updateColor();
    this->updateTexture();
    this->updateType();
    this->updateCubeId();
}

    void CubeRenderer::drawCubes(glm::mat4 view, glm::mat4 projection, interaction::LightManager& lightManager, const TextureArray& texture)
    {
      Renderer renderer;
  
      glm::mat4 MVMatrix = view;
      MVMatrix = glm::scale(MVMatrix, glm::vec3(2, 2, 2));

      glActiveTexture(GL_TEXTURE0);
	  glEnable(GL_CULL_FACE); 
      texture.Bind();

      if (lightManager.currentLight() == interaction::lightStatus::NONE) {
          m_ShaderCube->Bind();
          m_ShaderCube->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
		  renderer.DrawArraysInstanced(GL_POINTS, *m_VAO, *m_ShaderCube, m_CubeList.size());

      }
      else if (lightManager.currentLight() == interaction::lightStatus::DIRECTIONNAL) {
          m_ShaderCubeDirLight->Bind();
          m_ShaderCubeDirLight->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
          m_ShaderCubeDirLight->SetUniform3f("uKd", lightManager.dirLight().uKd.x, lightManager.dirLight().uKd.y, lightManager.dirLight().uKd.z);
          m_ShaderCubeDirLight->SetUniform3f("uKs", lightManager.dirLight().uKs.x, lightManager.dirLight().uKs.y, lightManager.dirLight().uKs.z);
          m_ShaderCubeDirLight->SetUniform3f("uLightDir_vs", lightManager.dirLight().lightDirection.x, lightManager.dirLight().lightDirection.y, lightManager.dirLight().lightDirection.z);
          m_ShaderCubeDirLight->SetUniform3f("uLightIntensity", lightManager.dirLight().lightIntensity.x, lightManager.dirLight().lightIntensity.y, lightManager.dirLight().lightIntensity.z);
          m_ShaderCubeDirLight->SetUniform1f("uShininess", lightManager.dirLight().shininess);
		  renderer.DrawArraysInstanced(GL_POINTS, *m_VAO, *m_ShaderCubeDirLight, m_CubeList.size());
      }
      else if (lightManager.currentLight() == interaction::lightStatus::PONCTUAL) {
          m_ShaderCubePonctLight->Bind();
          m_ShaderCubePonctLight->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
          m_ShaderCubePonctLight->SetUniform3f("uKd", lightManager.pointLightList()[0].uKd.x, lightManager.pointLightList()[0].uKd.y, lightManager.pointLightList()[0].uKd.z);
          m_ShaderCubePonctLight->SetUniform3f("uKs", lightManager.pointLightList()[0].uKs.x, lightManager.pointLightList()[0].uKs.y, lightManager.pointLightList()[0].uKs.z);
          m_ShaderCubePonctLight->SetUniform3f("uLightPos", lightManager.pointLightList()[0].lightPosition.x, lightManager.pointLightList()[0].lightPosition.y, lightManager.pointLightList()[0].lightPosition.z);
          m_ShaderCubePonctLight->SetUniform3f("uLightIntensity", lightManager.pointLightList()[0].lightIntensity.x, lightManager.pointLightList()[0].lightIntensity.y, lightManager.pointLightList()[0].lightIntensity.z);
          m_ShaderCubePonctLight->SetUniform1f("uShininess", lightManager.pointLightList()[0].shininess);
		  renderer.DrawArraysInstanced(GL_POINTS, *m_VAO, *m_ShaderCubePonctLight, m_CubeList.size());
      }
	  glDisable(GL_CULL_FACE);
	  texture.Bind();
    }

    void CubeRenderer::drawSelector(const glm::vec3 &position, const int &scale,
                                std::shared_ptr<Texture> texture,
                                glm::mat4 view, glm::mat4 projection)
    {
      Renderer renderer;
      glDisable(GL_DEPTH_TEST);
      GLCall(glLineWidth(5));

      glm::mat4 MVMatrix = glm::mat4(1.0f);
      MVMatrix = glm::scale(MVMatrix, glm::vec3((scale)+1, (scale)+1, (scale)+1));
      MVMatrix = view * MVMatrix;
      
      texture->Bind();
      m_ShaderSelector->Bind();
      m_ShaderSelector->SetUniform3f("uPosition", position.x, position.y, position.z);
      m_ShaderSelector->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);

	  renderer.DrawArrays(GL_POINTS, *m_VAO, *m_ShaderSelector, 1);
      glEnable(GL_DEPTH_TEST);
      texture->Unbind();
    };

    void CubeRenderer::drawSelectionTexture(const glm::mat4& view, const glm::mat4& projection) {
       
        GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glClearColor(1, 1, 1, 0); // White for unselectable air
        glViewport(0, 0, App::WINDOW_WIDTH, App::WINDOW_HEIGHT);
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 MVMatrix = view;
		MVMatrix = glm::scale(MVMatrix, glm::vec3(2, 2, 2));

        m_VAO->Bind();
        m_ShaderClickSelection->Bind();
        m_ShaderClickSelection->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
        GLCall(glDrawArraysInstanced(GL_POINTS, 0, m_CubeList.size(), m_CubeList.size()));

    }

    void CubeRenderer::updatePosition() {
        std::vector<glm::ivec3> positions;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&positions](Forms::Cube& cube) {
            positions.push_back(cube.position());
        });
        m_VertexBufferPosition->Update(positions.data(), sizeof(glm::ivec3) * positions.size());
    }

    void CubeRenderer::updateColor() {
        std::vector<glm::vec3> colors;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&colors](Forms::Cube& cube) {
            colors.push_back(cube.color());
        });
        m_VertexBufferColor->Update(colors.data(), sizeof(glm::vec3) * colors.size());
    }

    void CubeRenderer::updateTexture() {
        std::vector<unsigned int> textures;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&textures](Forms::Cube& cube) {
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
            [&types](Forms::Cube& cube) {
            types.push_back(cube.type());
        });
        m_VertexBufferType->Update(types.data(), sizeof(int) * types.size());
    }


    void CubeRenderer::updateCubeId() {
        std::vector<uint32_t> cubeId;
        std::for_each(m_CubeList.begin(), m_CubeList.end(),
            [&cubeId](Forms::Cube& cube) {
						
			    GLuint idPart[2];
				idPart[0] = (intptr_t(&cube) & 0xFFFFFFFF00000000) >> 32;
				idPart[1] = (intptr_t(&cube) & 0xFFFFFFFF);

            cubeId.push_back(idPart[0]);
            cubeId.push_back(idPart[1]);
        });
        m_VertexBufferCubeId->Update(cubeId.data(), 2 * sizeof(unsigned int) * m_CubeList.size());
    };

} // namespace renderer
