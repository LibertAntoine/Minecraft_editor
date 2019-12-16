
#include "ModePlanette.h"

#include "Renderer.h"

#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "forms/Cube.h"
#include <SDL.h>

namespace mode {

	ModePlanette::ModePlanette()
		: m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
	{
		float fov = glm::radians(70.f);
		float ratio = 800. / 600.;
		m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);

		m_CubeRenderer.add(form::Cube(glm::vec3(0, 0, 0), "IMAC.png", 1));
		m_CubeRenderer.add(form::Cube(glm::vec3(2, 2, 2), "IMAC.png", 1));
		m_CubeRenderer.add(form::Cube(glm::vec3(0, 2, 2), "IMAC.png", 1));

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


		default:
			break;
		}
	}


	void ModePlanette::OnRender()
	{

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix);
	}


	void ModePlanette::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}