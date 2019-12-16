
#include "ModePlanette.h"

#include "Renderer.h"
#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "forms/Cube.h"

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
	}

	ModePlanette::~ModePlanette()
	{

	}

	void ModePlanette::OnUpdate(float deltaTime)
	{

	}

	void ModePlanette::OnRender()
	{

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;

		{
			glm::mat4 model = glm::mat4(1.0f);

			//On consid�re s�par�ment la matrice de projection, celle simulant le placement de la cam�ra et celle simulant le placement de l'objet.
			// C'est le mod�le MVP. 
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			//D�finit les outils de dessin.
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

	}


	void ModePlanette::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}