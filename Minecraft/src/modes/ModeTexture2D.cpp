#include "ModeTexture2D.h"

#include "Renderer.h"
#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace mode {

	ModeTexture2D::ModeTexture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
		m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{

		float positions[] = {
			-50.0f,  -50.0f, 0.0f, 0.0f, //0
			 50.0f,  -50.0f, 1.0f, 0.0f, //1
			 50.0f,  50.0f, 1.0f, 1.0f, //2
			-50.0f,  50.0f, 0.0f, 1.0f  //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);


		m_Texture = std::make_unique<Texture>("res/textures/IMAC.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	ModeTexture2D::~ModeTexture2D()
	{

	}

	void ModeTexture2D::OnUpdate(float deltaTime)
	{

	}

	void ModeTexture2D::OnEvent(SDL_Event& e)
	{

	}


	void ModeTexture2D::OnRender()
	{

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;
		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);

			//On consid�re s�par�ment la matrice de projection, celle simulant le placement de la cam�ra et celle simulant le placement de l'objet.
			// C'est le mod�le MVP. 
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			//D�finit les outils de dessin.
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);
		}
	
	}


	void ModeTexture2D::OnImGuiRender()
	{
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);          // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}