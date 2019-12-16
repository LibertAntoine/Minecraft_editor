#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <algorithm>
#include "forms/Cube.h"


namespace renderer {


	class CubeRenderer 
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;	
		std::unique_ptr<Texture> m_Texture;
		std::vector<form::Cube> m_CubeList;

	public:
		CubeRenderer();
		~CubeRenderer();
		void add(const form::Cube& cube);
		void del(form::Cube* cube);
		void draw(glm::mat4 view, glm::mat4 projection);
	};

}