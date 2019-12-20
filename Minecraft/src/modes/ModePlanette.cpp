#include "ModePlanette.h"
#include "ImGUI/imgui.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include <SDL.h>

namespace mode {

  ModePlanette::ModePlanette()
    : m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
    m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)), 
    m_CubeRenderer(),
    m_CubeSelector(m_CubeRenderer,
        2048), // Obligatoirement une puissance de deux.
    m_backgroundColor(0.3f, 0.3f, 0.3f)

  {
    constexpr float fov = glm::radians(70.f);
    float ratio = 1080. / 720.;
    m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);

    m_CubeSelector.Create(glm::vec3(0, 0, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 4, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 8, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 12, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 16, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 20, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 24, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 28, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 32, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 36, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 40, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 44, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 48, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 52, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 56, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 60, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 64, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 68, 0), "IMAC.png", 1);
    m_CubeSelector.Create(glm::vec3(0, 72, 0), "IMAC.png", 1);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // NOTE: Selection related stuff
    m_textureSelection.EmptyTexture();
    m_frameBufferSelection.Bind();
    m_textureSelection.SimpleBind();
    //m_depthBufferSelection.Bind();
    // TODO: adapt to screen size dynamically
    //GLCall( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1080, 720); )
    //GLCall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferSelection.getDepthBufferId()); )
    GLCall( glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textureSelection.GetTextureID(), 0); )
    // TODO: POSSIBLE CONFLICT with these lines and normal framebuffer
    GLCall( GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0}; )
    GLCall( glDrawBuffers(1, DrawBuffers); )
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Problem with the framebuffer" << std::endl;

    m_textureSelection.Unbind();
    m_frameBufferSelection.Unbind();
    //m_depthBufferSelection.Unbind();

  }

  ModePlanette::~ModePlanette() {}

  void ModePlanette::OnUpdate(float deltaTime) {}

  void ModePlanette::OnEvent(SDL_Event &e) {
    switch (e.key.keysym.sym) {

      // TRACK CAM CONTROL //
      /*
         case 'j' : // Left
         m_TrackCam.rotateLeft(1.f);
         break;
         case 'l': // Right
         m_TrackCam.rotateLeft(-1.f);
         break;
         case 'i': // Up
         m_TrackCam.rotateUp(1.f);
         break;
         case 'k': // Down
         m_TrackCam.rotateUp(-1.f);
         break;
         */
      // FREE CAM CONTROL //
      case 'f': // Left
        m_FreeCam.rotateLeft(1.f);
        break;
      case 'h': // Right
        m_FreeCam.rotateLeft(-1.f);
        break;
      case 't': // Top
        m_FreeCam.rotateUp(1.f);
        break;
      case 'g': // Bottom
        m_FreeCam.rotateUp(-1.f);
        break;
      case 'q': // Left
        m_FreeCam.moveLeft(1.f);
        break;
      case 'd': // Right
        m_FreeCam.moveLeft(-1.f);
        break;
      case 'z': // Top
        m_FreeCam.moveFront(1.f);
        break;
      case 's': // Bottom
        m_FreeCam.moveFront(-1.f);
        break;
      case 'a': // Top
        m_FreeCam.moveUp(1.f);
        break;
      case 'w': // Bottom
        m_FreeCam.moveUp(-1.f);
        break;

        // KEY SELECTOR //
      case 'k': // back
        m_CubeSelector.MoveSelector(glm::vec3(0, 0, 1));
        break;
      case 'i': // front
        m_CubeSelector.MoveSelector(glm::vec3(0, 0, -1));
        break;
      case 'u': // up
        m_CubeSelector.MoveSelector(glm::vec3(0, 1, 0));
        break;
      case ',': // down
        m_CubeSelector.MoveSelector(glm::vec3(0, -1, 0));
        break;
      case 'l': // right
        m_CubeSelector.MoveSelector(glm::vec3(1, 0, 0));
        break;
      case 'j': // left
        m_CubeSelector.MoveSelector(glm::vec3(-1, 0, 0));
        break;

      case 'p': // Add Cube at the current selection.
        m_CubeSelector.AddToSelector();
        break;
      case 'o': // Delete Cube at the current selection.
        m_CubeSelector.DeleteToSelector();
        break;
      case ':': // Delete Cube at the current selection.
        m_CubeSelector.MoveIn();
        break;
      case '!': // Delete Cube at the current selection.
        m_CubeSelector.MoveOut();
        break;
      case '*': // Delete Cube at the current selection.
        m_CubeSelector.Extrude();
        break;
      case '$': // Delete Cube at the current selection.
        m_CubeSelector.Dig();
        break;

      default:
        break;
    }
  }

  void ModePlanette::OnRender() {

    GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y,
          m_backgroundColor.z, 1.0f));
    // TODO: Check if necessary (redundancy) because of App.cpp beginFrame()
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix);
    m_GridRenderer.draw(m_FreeCam, m_ProjMatrix);
    m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);


    m_frameBufferSelection.Bind();
    glClearColor(255,255,255,255);
    glViewport(0, 0, 1080, 720);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_CubeSelectionRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_CubeRenderer.m_CubeList);

    GLuint color[4];
    glReadPixels(540, 360, 1, 1, GL_RGB, GL_UNSIGNED_INT, color);
    std::cout << "[" << color[0] << ","<< color[1] << ',' << color[2] << ',' << color[3] << "]" << std::endl;

    m_frameBufferSelection.Unbind();


    //GLCall( glBindFramebuffer(GL_FRAMEBUFFER, GL_FRONT_LEFT); )

  }

  void ModePlanette::OnImGuiRender() {
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
} // namespace mode
