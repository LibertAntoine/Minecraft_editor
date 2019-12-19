#include "CubeRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace renderer {
	CubeRenderer::CubeRenderer()
	{
		form::CubeData cubeData;

		m_Shader = std::make_unique<Shader>("res/shaders/3D.shader");

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(cubeData.datas, 6 * 4 * 8 * sizeof(int));

		VertexBufferLayout layout;
		layout.Push<int>(3);
		layout.Push<int>(3);
		layout.Push<int>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(cubeData.indices, 6 * 6);

		m_Shader->Bind();
		m_Shader->SetUniform1i("uTexture", 0);
	}

	CubeRenderer::~CubeRenderer() {}

	form::Cube* CubeRenderer::add(const form::Cube& cube) {
		m_CubeList.push_back(cube);
		return &m_CubeList.back();
	}

	void CubeRenderer::del(form::Cube* cube) {
		m_CubeList.remove(*cube);
	}

	void CubeRenderer::draw(glm::mat4 view, glm::mat4 projection) {
		Renderer renderer;
		std::for_each(m_CubeList.begin(), m_CubeList.end(), [this, &renderer, &view, &projection](form::Cube& cube) {
			glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), cube.position());
			MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5 * cube.scale(), 0.5 * cube.scale(), 0.5 * cube.scale()));
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			MVMatrix = view * MVMatrix;
			cube.texture()->Bind();
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_Shader->SetUniformMat4f("uNormalMatrix", NormalMatrix);

			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);
			});
	}

	void CubeRenderer::drawSelector(const glm::vec3& position, const int& scale, std::shared_ptr<Texture> texture, glm::mat4 view, glm::mat4 projection) {
		Renderer renderer;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		texture->Bind();
		glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), position);
		MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5 * scale + 0.03, 0.5 * scale + 0.03, 0.5 * scale + 0.03));
		glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
		MVMatrix = view * MVMatrix;
		m_Shader->Bind();
		GLCall(glLineWidth(5));

		m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
		m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
		m_Shader->SetUniformMat4f("uNormalMatrix", NormalMatrix);

		renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);
	};

}
