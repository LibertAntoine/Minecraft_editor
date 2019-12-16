
#include "ModePlanette.h"

#include "Renderer.h"
#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>

namespace mode {

	ModePlanette::ModePlanette()
		: m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
	{
		form::Cube cube(glm::vec3(1, 1, 1));

		m_Shader = std::make_unique<Shader>("res/shaders/3D.shader");
		m_VAO = std::make_unique<VertexArray>();

		form::CubeData cubeData;

		m_VertexBuffer = std::make_unique<VertexBuffer>(cubeData.datas, 6 * 4 * 8 * sizeof(int));

		VertexBufferLayout layout;
		layout.Push<int>(3);
		layout.Push<int>(3);
		layout.Push<int>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(cubeData.indices, 6 * 6);

		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/blocks/log_acacia_top.png");
		m_Shader->SetUniform1i("uTexture", 0);


		m_CubeVect.push_back(form::Cube(glm::vec3(0, 0, 0), "IMAC.png", 1));
		m_CubeVect.push_back(form::Cube(glm::vec3(2, 2, 2), "IMAC.png", 1));
		m_CubeVect.push_back(form::Cube(glm::vec3(0, 2, 2), "IMAC.png", 1));
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
		Renderer renderer;
		m_Texture->Bind();
		float fov = glm::radians(70.f);
		float ratio = 800. / 600.;
		m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);

		std::for_each(m_CubeVect.begin(), m_CubeVect.end(), [this, &renderer](form::Cube& cube) {
			glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), cube.position());
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			MVMatrix = m_FreeCam.getViewMatrix() * MVMatrix;
			m_Shader->Bind();

			m_Shader->SetUniformMat4f("uMVPMatrix", m_ProjMatrix * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_Shader->SetUniformMat4f("uNormalMatrix", NormalMatrix);
			
			//D�finit les outils de dessin.
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

			});
	}


	void ModePlanette::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
