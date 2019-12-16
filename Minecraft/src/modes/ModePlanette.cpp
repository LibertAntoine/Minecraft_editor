
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

		const int datas[] = {
			// Front v0,v1,v2,v3
			 1,  1,  1,       0,  0,  1,       1, 0,
			-1,  1,  1,       0,  0,  1,       0, 0,
			-1, -1,  1,       0,  0,  1,       0, 1,
			 1, -1,  1,       0,  0,  1,       1, 1,
			 // Right v0,v3,v4,v5
			  1,  1,  1,       1,  0,  0,       0, 0,
			  1, -1,  1,       1,  0,  0,       0, 1,
			  1, -1, -1,       1,  0,  0,       1, 1,
			  1,  1, -1,       1,  0,  0,       1, 0,
			  // Top v0,v5,v6,v1	
			   1,  1,  1,       0,  1,  0,       0, 1,
			   1,  1, -1,       0,  1,  0,       1, 0,
			  -1,  1, -1,       0,  1,  0,       0, 0,
			  -1,  1,  1,       0,  1,  0,       1, 1,
			  // Left v1,v6,v7,v2	
			  -1,  1,  1,      -1,  0,  0,       1, 0,
			  -1,  1, -1,      -1,  0,  0,       0, 0,
			  -1, -1, -1,      -1,  0,  0,       0, 1,
			  -1, -1,  1,      -1,  0,  0,       1, 1,
			  // Bottom v7,v4,v3,v2
			  -1, -1, -1,       0, -1,  0,       1, 0,
			   1, -1, -1,       0, -1,  0,       0, 0,
			   1, -1,  1,       0, -1,  0,       0, 1,
			  -1, -1,  1,       0, -1,  0,       1, 1,
			  // Back v4,v7,v6,v5	
			   1, -1, -1,       0,  0, -1,       0, 1,
			  -1, -1, -1,       0,  0, -1,       1, 1,
			  -1,  1, -1,       0,  0, -1,       1, 0,
			   1,  1, -1,       0,  0, -1,       0, 0
		};

		const unsigned int indices[] = {
		 0, 1, 2,   2, 3, 0,      // front
		 4, 5, 6,   6, 7, 4,      // right
		 8, 9,10,  10,11, 8,      // top
		12,13,14,  14,15,12,      // left
		16,17,18,  18,19,16,      // bottom
		20,21,22,  22,23,20		  // back
		};

		m_VertexBuffer = std::make_unique<VertexBuffer>(datas, 6 * 4 * 8 * sizeof(int));

		VertexBufferLayout layout;
		layout.Push<int>(3);
		layout.Push<int>(3);
		layout.Push<int>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6 * 6);

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