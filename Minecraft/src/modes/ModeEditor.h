#pragma once

#include "Mode.h"

#include "Camera.h"
#include "DepthBuffer.h"
#include "FrameBuffer.h"
#include "Interaction/CubeSelector.h"
#include "Interaction/Interface.h"
#include "Renderer/CubeRenderer.h"
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

class ModeEditor : public Mode
{
private:
  glm::mat4 m_ProjMatrix;
  renderer::GridRenderer m_GridRenderer;
	std::shared_ptr<renderer::CubeRenderer> m_CubeRenderer;
	std::shared_ptr<TextureArray> m_textureArray;
	std::shared_ptr<interaction::CubeSelector> m_CubeSelector;
	std::shared_ptr<glm::vec3> m_backgroundColor;
  renderer::GroundSelectionRenderer m_GroundSelectionRenderer;
	std::shared_ptr<camera::FreeflyCamera> m_FreeCam;
	std::shared_ptr<interaction::LightManager> m_LightManager;
  interaction::Interface m_Interface;
  FrameBuffer m_frameBufferSelection; /// Custom framebuffer that is bound during selection texture rendering, also for queries
  DepthBuffer m_depthBufferSelection;
  Texture m_textureSelectionCube; /// Offscreen texture that contains mouse selectable(visible) Cubes
  Texture m_textureSelectionGround; /// Offscreen texture that contains mouse selectable (visible) ground
  bool m_moveCamEye = false;
  bool m_moveShift = false;
  bool m_slideMouse = false;

  bool m_altKey = false;
  bool m_ctrlKey = false;
  bool m_spaceKey = false;
  bool m_shiftKey = false;

  bool m_leftClick = false;
  bool m_rightClick = false;
  bool m_middleClick = false;



public:
  ModeEditor();
  ~ModeEditor();
  void OnUpdate(float ) override;
  void OnEvent(const SDL_Event &e) override;
  void OnRender() override;
  void OnImGuiRender() override;

  inline glm::vec3& backgroundColor() { return  *m_backgroundColor; };
  inline camera::FreeflyCamera& freeCam() { return  *m_FreeCam; };
  inline interaction::CubeSelector& cubeSelector() { return  *m_CubeSelector; };
  inline interaction::LightManager& lightManager() { return  *m_LightManager; };

	void resetInteractionBool();

};
} // namespace modes
