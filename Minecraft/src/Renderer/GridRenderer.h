#pragma once

#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <algorithm>
#include "forms/Grid.h"


namespace renderer {


	class GridRenderer
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		form::Grid m_grid;

	public:
		GridRenderer(const unsigned int& size, glm::vec3 color);
		~GridRenderer();
		void draw(glm::mat4 view, glm::mat4 projection);
	};

}
