#include "GridRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace renderer {
	GridRenderer::GridRenderer(const unsigned int& size, glm::vec3 color)
		:m_grid(form::Grid(size, color))
	
	{
		m_Shader = std::make_unique<Shader>("res/shaders/3DGrid.shader");

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(m_grid.datas().data(), 8.f * (size + 1.0f) * 3.f * sizeof(int));

		VertexBufferLayout layout;
		layout.Push<int>(3);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(m_grid.indices().data(), 8 * (size + 1));

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", color.x, color.y, color.z, 0.3f);

	}


	GridRenderer::~GridRenderer() {}

	void GridRenderer::draw(const camera::FreeflyCamera& camera, const glm::mat4& projection) {
			Renderer renderer;
			glm::mat4 MVMatrix = glm::mat4(1);
			MVMatrix = MVMatrix * camera.getViewMatrix();


			/*
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			renderer.Draw(GL_LINES, *m_VAO, *m_IndexBuffer, *m_Shader);
			*/
			
			MVMatrix = glm::rotate(MVMatrix, glm::pi<float>()/2, glm::vec3(1.f, 0.f, 0.f));
			MVMatrix = glm::translate(MVMatrix, glm::vec3(round(camera.position().x), round(camera.position().y), 0.f));
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			renderer.Draw(GL_LINES, *m_VAO, *m_IndexBuffer, *m_Shader);
			
			/*
			MVMatrix = glm::rotate(MVMatrix, glm::pi<float>() / 2, glm::vec3(0.f, 1.f, 0.f));
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			renderer.Draw(GL_LINES, *m_VAO, *m_IndexBuffer, *m_Shader);
			*/
	}

	}