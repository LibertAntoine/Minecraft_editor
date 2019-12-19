
#include "ModePlanette.h"
#include "Renderer.h"
#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>

namespace mode {

	ModePlanette::ModePlanette()
		: m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)),
		m_CubeRenderer(),
		m_CubeSelector(m_CubeRenderer, 2048), //Obligatoirement une puissance de deux.
		m_backgroundColor(0.3f, 0.3f, 0.3f)

	{
		constexpr float fov = glm::radians(70.f);
		float ratio = 1080. / 720.;
		m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);



		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
	}

  ModePlanette::~ModePlanette()
  {

  }

  void ModePlanette::OnUpdate(float deltaTime)
  {
  }

  void ModePlanette::OnEvent(SDL_Event& e)
  {
    switch (e.key.keysym.sym)
    {

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
	  case ':': // Block selection on Cube at the current selection.
		  m_CubeSelector.MoveIn();
		  break;
	  case '!': // Move the Cube selected.
		  m_CubeSelector.MoveOut();
		  break;
	  case '*': // Extrude the current y axe.
		  m_CubeSelector.Extrude();
		  break;
	  case '$': // Dig the current y axe.
		  m_CubeSelector.Dig();
		  break;





      default:
        break;
    }
  }


  void ModePlanette::OnRender()
  {

		GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix);
		m_GridRenderer.draw(m_FreeCam, m_ProjMatrix);
		m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);
	}


  void ModePlanette::OnImGuiRender()
  {
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	ImGui::Begin("Selector Menu");                        
	if (ImGui::Button("Add Cube")) m_CubeSelector.AddToSelector();
	if (ImGui::Button("Delete Cube")) m_CubeSelector.DeleteToSelector();
	if (ImGui::Button("Select")) m_CubeSelector.MoveIn();
	if (ImGui::Button("Move Selection")) m_CubeSelector.MoveOut();
	if (ImGui::Button("Extrude")) m_CubeSelector.Extrude();
	if (ImGui::Button("Dig")) m_CubeSelector.Dig();
	ImGui::End();

	ImGui::Begin("Selector Move");
	if (ImGui::Button("MoveLeft")) m_CubeSelector.MoveSelector(glm::vec3(-1, 0, 0));
	if (ImGui::Button("MoveRight")) m_CubeSelector.MoveSelector(glm::vec3(1, 0, 0));
	if (ImGui::Button("MoveUp")) m_CubeSelector.MoveSelector(glm::vec3(0, 1, 0));
	if (ImGui::Button("MoveDown")) m_CubeSelector.MoveSelector(glm::vec3(0, -1, 0));
	if (ImGui::Button("MoveFront")) m_CubeSelector.MoveSelector(glm::vec3(0, 0, -1));
	if (ImGui::Button("MoveBack")) m_CubeSelector.MoveSelector(glm::vec3(0, 0, 1));
	ImGui::End();



	ImGui::Begin("Camera Controller");
	if (ImGui::Button("RotateUp")) m_FreeCam.rotateUp(1.f);
	if (ImGui::Button("RotateDown")) m_FreeCam.rotateUp(-1.f);
	if (ImGui::Button("RotateLeft")) m_FreeCam.rotateLeft(1.f);
	if (ImGui::Button("RotateRight")) m_FreeCam.rotateLeft(-1.f);
	if (ImGui::Button("ZoomIn")) m_FreeCam.moveFront(1.f);
	if (ImGui::Button("ZoomOut")) m_FreeCam.moveFront(-1.f);
	if (ImGui::Button("MoveLeft")) m_FreeCam.moveLeft(1.f);
	if (ImGui::Button("MoveRight")) m_FreeCam.moveLeft(-1.f);
	if (ImGui::Button("MoveUp")) m_FreeCam.moveUp(1.f);
	if (ImGui::Button("MoveDown")) m_FreeCam.moveUp(-1.f);
	ImGui::End();



  }
}
