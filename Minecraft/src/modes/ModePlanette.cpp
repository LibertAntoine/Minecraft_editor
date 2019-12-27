#include "ModePlanette.h"
#include <stdint.h>
#include "ImGUI/imgui.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>
#include <string>

namespace modes {

  ModePlanette::ModePlanette()
    : m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
    m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)), m_CubeRenderer(),
    m_CubeSelector(m_CubeRenderer, 2048), // Obligatoirement une puissance de deux.
    m_backgroundColor(0.3f, 0.3f, 0.3f),
    m_GroundSelectionRenderer(200)

  {
    constexpr float fov = glm::radians(70.f);
    float ratio = 1080. / 720.;
    m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);



    // TODO: check the following if necessary
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

    /* 
       m_CubeSelector.Create(glm::vec3(0, 0, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 2, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 4, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 6, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 8, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 10, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 12, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 14, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 16, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 18, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 20, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 22, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 24, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       */

    // TODO: check the following if necessary
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // NOTE: Selection related stuff
    m_textureSelectionCube.EmptyTextureUI();
    m_textureSelectionGround.EmptyTextureI();

    m_frameBufferSelection.Bind();

    m_textureSelectionCube.SimpleBind();
    //m_depthBufferSelection.Bind();

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureSelectionCube.GetTextureID(), 0););

    m_textureSelectionCube.SimpleBind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textureSelectionGround.GetTextureID(), 0););

    //GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    //GLCall(glDrawBuffers(2, DrawBuffers););

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
      std::cout << "Problem with the framebuffer" << std::endl;

    m_textureSelectionGround.Unbind();
    m_frameBufferSelection.Unbind();
    //m_depthBufferSelection.Unbind();
  }

  ModePlanette::~ModePlanette() {}

  void ModePlanette::OnUpdate(float deltaTime) {}

  void ModePlanette::OnRender()
  {

    GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y,
          m_backgroundColor.z, 1.0f));
    // TODO: Check if necessary (redundancy) because of App.cpp beginFrame()
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_GridRenderer.draw(m_FreeCam, m_ProjMatrix, m_CubeSelector.activeGrid());
	m_LightManager.dirLight().lightDirection = glm::vec3(glm::mat4(1.0f) * glm::vec4(m_LightManager.direction(), 0));
    m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_LightManager);
    m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);

    // NOTE: Generating offscreen selection texture
    m_frameBufferSelection.Bind();
    m_CubeSelectionRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_CubeRenderer.m_CubeList);
    m_GroundSelectionRenderer.draw(m_FreeCam, m_ProjMatrix, m_CubeSelector.activeGrid());
    m_frameBufferSelection.Unbind();

  }

  void ModePlanette::OnEvent(const SDL_Event &e)
  {
    switch(e.type) {
      case SDL_MOUSEBUTTONDOWN:
        if ( e.button.button == SDL_BUTTON_LEFT  && ImGui::IsAnyWindowHovered() == false ) {

          /* NOTE: check which FrameBuffer is currently bound
             GLint drawFboId = 0, readFboId = 0;
             glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
             glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
          //std::cout << "checking current FBO. Draw:" << drawFboId << ", Read: " << readFboId << std::endl;
          */

          // NOTE: Check if a cube has been selected
          m_frameBufferSelection.Bind();
          GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
          GLuint pixels[4] = {0,0,0,0};
          GLCall( glReadPixels(e.button.x, 960-e.button.y-1, 1, 1, GL_RGBA_INTEGER, GL_UNSIGNED_INT, pixels) );
          //std::cout << pixels[0] << "," << pixels[1] << "," << pixels[2] << "," << pixels[3] << std::endl;
          if ( pixels[3] != 0 ) {
            form::Cube* selectionAddress;
            // NOTE: Rebuild the pointer address (64-bit) using two 32-bit values
            selectionAddress = (form::Cube*)( (intptr_t( pixels[0] ) << 32 & 0xFFFFFFFF00000000) | ( intptr_t( pixels[1] ) & 0xFFFFFFFF ) );
            m_CubeSelector.SetSelector(glm::ivec3(selectionAddress->position()));
          } else {
            GLint position[4];
            GLCall( glReadBuffer(GL_COLOR_ATTACHMENT1); );
            GLCall( glReadPixels(e.button.x, 960-e.button.y-1, 1, 1, GL_RGBA_INTEGER, GL_INT, position) );
            //std::cout << "PosX: " << position[0] << ", PosY: " << position[1] << std::endl;
            if ( position[3] != 0 ) {
              m_CubeSelector.SetSelector(glm::ivec3(position[0], 0, position[1]));
            }
          }
          m_frameBufferSelection.Unbind();        

          // TODO: Detect IMGUI hover and do not triger selection
          // TODO: Add floor checking
        }
        break;
    }
  }



  void ModePlanette::OnImGuiRender()
  {
    m_Interface.MenuBarInterface(m_FreeCam, m_CubeSelector);
    m_Interface.MainActionMenu(m_CubeSelector, m_FreeCam, m_LightManager, m_backgroundColor);
    m_Interface.MenuInfosInterface(m_FreeCam, m_CubeSelector, m_CubeRenderer);
  }
} // namespace modes
