#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include "forms/Cube.h"
#include <octree/octree.h>
#include <Renderer/CubeRenderer.h>

namespace interaction {

	typedef struct Selector {
		const char* selectorTexture;
		glm::vec3 selectorPosition;
		int selectorScale;
	} Selector;

	class CubeSelector
	{
	private:
		renderer::CubeRenderer* m_Cuberenderer;
		Octree<form::Cube*> m_CubeWorld; // Documentation : https://nomis80.org/code/doc/classOctree.html
		int m_SizeWorld;
		Selector* m_selector;
		std::unique_ptr<Texture> m_textSelector;

	public:
		CubeSelector() = delete;
		CubeSelector(renderer::CubeRenderer& renderer, const int& capacity = 2024);
		~CubeSelector();
		void Create(const glm::vec3& position, const char* textName, const int& scale);
		void Move(form::Cube* cube, const glm::vec3& NewPosition);
		void MoveSelector(const glm::vec3& deplacement);
		void AddToSelector();
		void DeleteToSelector();
		void Show(glm::mat4 view, glm::mat4 projection);
		form::Cube* currentCube();

	};

}
#pragma once
