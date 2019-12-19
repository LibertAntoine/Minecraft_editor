#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include <list>

#include "Shader.h"
#include "forms/Cube.h"

namespace renderer {

	class CubeSelectionRenderer 
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;	


	public:
		CubeSelectionRenderer();
		~CubeSelectionRenderer();
		void draw(glm::mat4 view, glm::mat4 projection, std::list<form::Cube>& cubeList);
	};

}
