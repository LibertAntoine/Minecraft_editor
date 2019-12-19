#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include <list>
#include "forms/Cube.h"

namespace renderer {

	class CubeRenderer 
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_ShaderTexture;
		std::unique_ptr<Shader> m_ShaderColor;
		std::unique_ptr<Texture> m_Texture;


	public:
		std::list<form::Cube> m_CubeList;
		CubeRenderer();
		~CubeRenderer();
		form::Cube* add(const form::Cube& cube);
		void del(form::Cube* cube);
		void draw(glm::mat4 view, glm::mat4 projection);
		void drawSelector(const glm::vec3& position, const int& scale, std::shared_ptr<Texture> texture, glm::mat4 view, glm::mat4 projection);
	};

}
