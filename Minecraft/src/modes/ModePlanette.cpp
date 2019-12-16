
#include "ModePlanette.h"

#include "Renderer.h"
#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "forms/Cube.h"
#include <SDL.h>

namespace mode {

	ModePlanette::ModePlanette()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
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

		m_Texture = std::make_unique<Texture>("res/textures/IMAC.png");
		m_Shader->SetUniform1i("uTexture", 0);
	}

	ModePlanette::~ModePlanette()
	{

	}

	void ModePlanette::OnUpdate(float deltaTime)
	{
		TrackCam.rotateLeft(1.f);
		TrackCam.rotateUp(1.f);
	}

	void ModePlanette::OnRender()
	{

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;
		m_Texture->Bind();
		float fov = glm::radians(70.f);
		float ratio = 800. / 600.;
		{
			glm::mat4 ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);
			glm::mat4 MVMatrix = glm::mat4(1.0f);
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			MVMatrix = TrackCam.getViewMatrix() * MVMatrix;

			m_Shader->Bind();

			m_Shader->SetUniformMat4f("uMVPMatrix", ProjMatrix * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_Shader->SetUniformMat4f("uNormalMatrix", NormalMatrix);

			//D�finit les outils de dessin.
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

	}


	void ModePlanette::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}