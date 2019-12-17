#include "CubeRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace renderer {
	CubeRenderer::CubeRenderer() {
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
		m_Texture = std::make_unique<Texture>("res/textures/blocks/log_acacia_top.png");
		m_Shader->SetUniform1i("uTexture", 0);
	}

	CubeRenderer::~CubeRenderer() {}

	void CubeRenderer::add(const form::Cube& cube) {
		m_CubeList.push_back(cube);
	}

	void CubeRenderer::del(form::Cube* cube) {
	}

	void CubeRenderer::draw(glm::mat4 view, glm::mat4 projection) {
		Renderer renderer;
		m_Texture->Bind();
		std::for_each(m_CubeList.begin(), m_CubeList.end(), [this, &renderer, &view, &projection](form::Cube& cube) {
			glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f), cube.position());
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			MVMatrix = view * MVMatrix;
			m_Shader->Bind();

			m_Shader->SetUniformMat4f("uMVPMatrix", projection * MVMatrix);
			m_Shader->SetUniformMat4f("uMVMatrix", MVMatrix);
			m_Shader->SetUniformMat4f("uNormalMatrix", NormalMatrix);

			renderer.Draw(GL_TRIANGLES, *m_VAO, *m_IndexBuffer, *m_Shader);
			});
	}
}
