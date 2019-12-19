#pragma once


#include <iostream>
#include <vector>
#include <algorithm>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Camera.h"
#include "forms/Grid.h"
#include <memory>




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
		void draw(const camera::FreeflyCamera& camera, const glm::mat4& projection);
	};

}
