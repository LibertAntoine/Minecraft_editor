#pragma once

#include "Mode.h"

#include "Camera.h"
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "Interaction/CubeSelector.h"
#include "Interaction/Interface.h"
#include "Renderer/CubeRenderer.h"
#include "Renderer/CubeSelectionRenderer.h"
#include "Renderer/GroundSelectionRenderer.h"
#include "Renderer/GridRenderer.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "forms/Cube.h"
#include "Interaction/LightManager.h"
#include "TextureArray.h"
#include <algorithm>
#include <vector>


#include <memory>

namespace modes {

class ModePlanette : public Mode
{
private:
  glm::vec3 m_backgroundColor;
  glm::mat4 m_ProjMatrix;
  camera::FreeflyCamera m_FreeCam;
  renderer::GridRenderer m_GridRenderer;
  renderer::CubeRenderer m_CubeRenderer;
  renderer::CubeSelectionRenderer m_CubeSelectionRenderer;
  renderer::GroundSelectionRenderer m_GroundSelectionRenderer;
  interaction::CubeSelector m_CubeSelector;
  interaction::Interface m_Interface;
  interaction::LightManager m_LightManager;
  FrameBuffer m_frameBufferSelection; /// Custom framebuffer that is bound during selection texture rendering, also for queries
  //DepthBuffer m_depthBufferSelection;
  Texture m_textureSelectionCube; /// Offscreen texture that contains mouse selectable(visible) Cubes
  Texture m_textureSelectionGround; /// Offscreen texture that contains mouse selectable (visible) ground
  bool m_moveCamEye = false;
  bool m_moveShift = false;
  TextureArray m_textureArray;



public:
  ModePlanette();
  ~ModePlanette();
  void OnUpdate(float deltaTime) override;
  void OnEvent(const SDL_Event &e) override;
  void OnRender() override;
  void OnImGuiRender() override;

  inline glm::vec3& backgroundColor() { return  m_backgroundColor; };
  inline camera::FreeflyCamera& freeCam() { return  m_FreeCam; };
  inline interaction::CubeSelector& cubeSelector() { return  m_CubeSelector; };
  inline interaction::LightManager& lightManager() { return  m_LightManager; };

};
} // namespace modes
