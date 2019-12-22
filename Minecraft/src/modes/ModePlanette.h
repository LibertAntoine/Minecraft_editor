#pragma once

#include "Mode.h"

#include "Camera.h"
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "Interaction/CubeSelector.h"
#include "Interaction/Interface.h"
#include "Renderer/CubeRenderer.h"
#include "Renderer/CubeSelectionRenderer.h"
#include "Renderer/GridRenderer.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "forms/Cube.h"
#include <algorithm>
#include <vector>


#include <memory>

namespace mode {
class ModePlanette : public Mode
{
private:
  glm::vec3 m_backgroundColor;
  glm::mat4 m_ProjMatrix;
  camera::FreeflyCamera m_FreeCam;
  renderer::GridRenderer m_GridRenderer;
  renderer::CubeRenderer m_CubeRenderer;
  renderer::CubeSelectionRenderer m_CubeSelectionRenderer;
  interaction::CubeSelector m_CubeSelector;
  interaction::Interface m_Interface;
  FrameBuffer m_frameBufferSelection; /// Custom framebuffer that is bound during selection texture rendering, also for queries
  //DepthBuffer m_depthBufferSelection;
  Texture m_textureSelection; /// Offscreen texture that contains mouse selectable elements

public:
  ModePlanette();
  ~ModePlanette();
  void OnUpdate(float deltaTime) override;
  void OnEvent(const SDL_Event &e) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace mode
