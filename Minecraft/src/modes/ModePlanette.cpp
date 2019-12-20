#include "ModePlanette.h"
#include "ImGUI/imgui.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include <SDL.h>
#include <string>

namespace mode {

ModePlanette::ModePlanette()
    : m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
      m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)), m_CubeRenderer(),
      m_CubeSelector(m_CubeRenderer,
                     2048), // Obligatoirement une puissance de deux.
      m_backgroundColor(0.3f, 0.3f, 0.3f)

{
  constexpr float fov = glm::radians(70.f);
  float ratio = 1080. / 720.;
  m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_CULL_FACE);

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
  m_depthBufferSelection.Bind();
  // TODO: adapt to screen size dynamically
  GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1080, 720);)
          GLCall(glFramebufferRenderbuffer(
                     GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
                     m_depthBufferSelection.getDepthBufferId());)
              GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          m_textureSelection.GetTextureID(),
                                          0);)
      // TODO: POSSIBLE CONFLICT with these lines and normal framebuffer
      GLCall(GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};)
          GLCall(glDrawBuffers(1, DrawBuffers);)

              if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
                  GL_FRAMEBUFFER_COMPLETE) std::cout
      << "Problem with the framebuffer" << std::endl;

  m_frameBufferSelection.Unbind();
  m_textureSelection.Unbind();
  m_depthBufferSelection.Unbind();
}

ModePlanette::~ModePlanette()

    void ModePlanette::OnEvent(const SDL_Event &e)
{}

void ModePlanette::OnRender()
{

  GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y,
                      m_backgroundColor.z, 1.0f));
  // TODO: Check if necessary (redundancy) because of App.cpp beginFrame()
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  glEnable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  m_GridRenderer.draw(m_FreeCam, m_ProjMatrix);
  m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix);
  m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);
  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);

  m_frameBufferSelection.Bind();
  glClearColor(1, 1, 1, 1);
  glViewport(0, 0, 1080, 720);
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  m_CubeSelectionRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_CubeRenderer.m_CubeList);
  m_frameBufferSelection.Unbind();

  glEnable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);
  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);
}

void ModePlanette::OnImGuiRender()
{
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  m_Interface.SelectorInterface(m_CubeSelector);
  m_Interface.CameraInterface(m_FreeCam);

  ImGuiWindowFlags corner =
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

  bool open = true;
  ImGui::Begin("Test", &open, corner);
  ImGui::SetWindowPos(ImVec2(0, 500), true);
  ImGui::SetWindowSize(ImVec2(200, 200), true);

  ImGui::End();

  const float my_values[] = {0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f};
  ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

  ImGui::Begin("Infos Current Cube");
  if (m_CubeSelector.selector()->currentCube != nullptr) {
    ImGui::Text("Cube Scale : ");
    ImGui::InputInt("scalec",
                    m_CubeSelector.selector()->currentCube->scalePtr(), 1, 100);
    if (m_CubeSelector.selector()->currentCube->texture() != nullptr) {
      ImGui::Text("Cube Texture : ");
      ImGui::Text(
          m_CubeSelector.selector()->currentCube->texture()->name().c_str());
      if (ImGui::BeginCombo("Texture Cube", m_CubeSelector.selector()
                                                ->currentCube->texture()
                                                ->name()
                                                .c_str())) {
        for (int i = 0; i < m_CubeSelector.textureList()->nameList().size();
             ++i) {
          bool is_selected =
              (m_CubeSelector.selector()->currentCube->texture()->name() ==
               m_CubeSelector.textureList()->nameList()[i]);
          if (ImGui::Selectable(
                  m_CubeSelector.textureList()->nameList()[i].c_str(),
                  is_selected))
            m_CubeSelector.selector()->currentCube->texture(
                m_CubeSelector.textureList()->give(
                    m_CubeSelector.textureList()->nameList()[i]));
          if (is_selected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }
    } else {
      ImGui::Text("Cube Color : ");
      float r = m_CubeSelector.selector()->currentCube->color().x;
      float g = m_CubeSelector.selector()->currentCube->color().y;
      float b = m_CubeSelector.selector()->currentCube->color().z;
      if (ImGui::InputFloat("r", &r, 0.01f, 0.1f, "%.3f") ||
          ImGui::InputFloat("g", &g, 0.01f, 0.1f, "%.3f") ||
          ImGui::InputFloat("b", &b, 0.01f, 0.1f, "%.3f")) {
        m_CubeSelector.selector()->currentCube->Setcolor(glm::vec3(r, g, b));
      };
    ImGui::Text("Cube Position : ");
    int xc = m_CubeSelector.selector()->currentCube->position().x;
    int yc = m_CubeSelector.selector()->currentCube->position().y;
    int zc = m_CubeSelector.selector()->currentCube->position().z;
    if (ImGui::InputInt("x", &xc, 1, 100) ||
        ImGui::InputInt("y", &yc, 1, 100) ||
        ImGui::InputInt("z", &zc, 1, 100)) {
      m_CubeSelector.selector()->selectorPosition = glm::vec3(xc, yc, zc);
      m_CubeSelector.Move(m_CubeSelector.selector()->currentCube,
                          glm::vec3(xc, yc, zc));
    };
  }
  ImGui::End();
}
} // namespace mode
