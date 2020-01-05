#include "ModeEditor.h"
#include <stdint.h>
#include "ImGUI/imgui.h"
#include "GraphicEngine/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>
#include <string>
#include "stb_image/stb_image.h"
#include "GraphicEngine/GLerror.h"

namespace Modes {

	ModeEditor::ModeEditor()
	: m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)), m_CubeRenderer(std::make_shared<renderer::CubeRenderer>()),
	m_textureArray(std::make_shared<TextureArray>(32, 32)),
	m_CubeSelector(std::make_shared<interaction::CubeSelector>(m_CubeRenderer, 512)), // Should be a pow of two.
	m_backgroundColor(std::make_shared<glm::vec3>(0.3f, 0.3f, 0.3f)),
	m_FreeCam(std::make_shared<camera::FreeflyCamera>()),
	m_LightManager(std::make_shared<interaction::LightManager>()),
	m_Interface(m_CubeRenderer, m_CubeSelector, m_textureArray, m_FreeCam, m_LightManager, m_backgroundColor),
	m_KeyBoard(m_CubeRenderer, m_CubeSelector, m_FreeCam, &m_frameBufferSelection)
	{
    constexpr float fov = glm::radians(70.f);
    constexpr float ratio = (float)App::WINDOW_WIDTH / App::WINDOW_WIDTH;
    m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);


    m_textureArray->AddTexture("res/textures/Cube/log_acacia_top.png", "res/textures/Cube/log_acacia_top_proxi.png");
    m_textureArray->AddTexture("res/textures/Cube/piston_bottom.png", "res/textures/Cube/piston_bottom_proxi.png");
    m_textureArray->AddTexture("res/textures/Cube/bookshelf.png", "res/textures/Cube/bookshelf_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/brick.png", "res/textures/Cube/brick_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/coarse_dirt.png", "res/textures/Cube/coarse_dirt_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/cobblestone.png", "res/textures/Cube/cobblestone_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/crafting_table_front.png", "res/textures/Cube/crafting_table_front_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/lava_placeholder.png", "res/textures/Cube/lava_placeholder_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/glowstone.png", "res/textures/Cube/glowstone_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/grass_carried.png", "res/textures/Cube/grass_carried_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/grass_side.png", "res/textures/Cube/grass_side_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/planks_jungle.png", "res/textures/Cube/planks_jungle_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/prismarine_bricks.png", "res/textures/Cube/prismarine_bricks_proxi.png");
		m_textureArray->AddTexture("res/textures/Cube/sponge_wet.png", "res/textures/Cube/sponge_wet_proxi.png");
    
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // NOTE: Selection related stuff
    m_textureSelectionCube.EmptyTextureUI();
    m_textureSelectionGround.EmptyTextureI();

    m_frameBufferSelection.Bind();

    m_depthBufferSelection.Bind();
		GLCall( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, App::WINDOW_WIDTH, App::WINDOW_HEIGHT); );
		GLCall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferSelection.getDepthBufferId()); );

    m_textureSelectionCube.Bind();

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureSelectionCube.GetTextureID(), 0););

    m_textureSelectionCube.Bind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textureSelectionGround.GetTextureID(), 0););

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
      std::cout << "Problem with the framebuffer" << std::endl;

    m_textureSelectionGround.Unbind();
    m_frameBufferSelection.Unbind();
    m_depthBufferSelection.Unbind();

    m_CubeRenderer->updateColor();
    m_CubeRenderer->updateTexture();
    m_CubeRenderer->updateType();
    m_CubeRenderer->updateCubeId();
  }

  ModeEditor::~ModeEditor() {}

  void ModeEditor::OnUpdate(float ) {}

  void ModeEditor::OnRender()
  {

    GLCall(glClearColor(m_backgroundColor->x, m_backgroundColor->y, m_backgroundColor->z, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_GridRenderer.drawGrid(*m_FreeCam, m_ProjMatrix, m_CubeSelector->activeGrid());
	m_LightManager->dirLight().lightDirection = glm::vec3(glm::mat4(1.0f) * glm::vec4(m_LightManager->direction(), 0));
    m_LightManager->pointLightList()[0].lightPosition = glm::vec3(glm::mat4(1.0f) * glm::vec4(m_LightManager->position(), 0));
    m_CubeRenderer->drawCubes(m_FreeCam->getViewMatrix(), m_ProjMatrix, *m_LightManager, *m_textureArray);

	if (m_CubeSelector->selector()->selectorState == interaction::SelectorState::CUT)
		m_CubeRenderer->drawSelector(m_CubeSelector->selector()->selectedPosition,
			m_CubeSelector->selector()->selectorCube.scale(),
			m_CubeSelector->textSelected(), m_FreeCam->getViewMatrix(), m_ProjMatrix);
	m_CubeRenderer->drawSelector(m_CubeSelector->selector()->selectorCube.position(),
		m_CubeSelector->selector()->selectorCube.scale(), m_CubeSelector->textSelector(),
		m_FreeCam->getViewMatrix(), m_ProjMatrix);

    // NOTE: Generating offscreen selection texture
    m_frameBufferSelection.Bind();
		m_CubeRenderer->drawSelectionTexture(m_FreeCam->getViewMatrix(), m_ProjMatrix);
		m_GridRenderer.drawGridSelection(*m_FreeCam, m_ProjMatrix);
    m_frameBufferSelection.Unbind();

  }

  void ModeEditor::OnEvent(const SDL_Event& e)
  {
	  if (!ImGui::IsAnyWindowHovered() && !ImGui::IsAnyItemHovered()) {
		  switch (e.type) {
		  case SDL_MOUSEWHEEL:
			  m_FreeCam->moveFront(e.wheel.y);
			  break;

		  case SDL_MOUSEMOTION:
			  if (ImGui::IsMouseDown(SDL_BUTTON_MIDDLE) || ImGui::IsKeyPressed(SDL_SCANCODE_SPACE)) {

				  if (e.motion.xrel != 0) m_FreeCam->moveLeft(float(e.motion.xrel) * 0.01);
				  if (e.motion.yrel != 0) m_FreeCam->moveUp(float(e.motion.yrel) * 0.01);

			  }
			  else if (ImGui::IsKeyDown(SDL_SCANCODE_LSHIFT) || ImGui::IsKeyDown(SDL_SCANCODE_RSHIFT)) {

				  if (e.motion.xrel != 0) m_FreeCam->rotateLeft(-float(e.motion.xrel) * 0.5);
				  if (e.motion.yrel != 0) m_FreeCam->rotateUp(-float(e.motion.yrel) * 0.5);

			  }
		  }
	  }
  }


  void ModeEditor::OnImGuiRender()
  {
	/* Activation ImGUI interface */
    m_Interface.MenuBarInterface();
    m_Interface.MainActionMenu();
    m_Interface.MenuInfosInterface();

	/* Activation KeyBoard Controllers */
	m_KeyBoard.CameraShortCut();
	m_KeyBoard.CubeShortCut();
	m_KeyBoard.SelectorShortCut();
	m_KeyBoard.MouseShortCut();
  }
} // namespace modes
