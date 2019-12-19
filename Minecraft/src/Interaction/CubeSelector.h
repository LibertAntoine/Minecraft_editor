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
#include "CubeTextureList.h"

namespace interaction {

	typedef struct Selector {
		Texture* selectorTexture;
		glm::vec3 selectorPosition;
		int selectorScale;
		bool currentSelected;
		bool currentCopy;
		glm::vec3 selectedPosition;
	} Selector;

	class CubeSelector
	{
	private:
		renderer::CubeRenderer* m_Cuberenderer;
		Octree<form::Cube*> m_CubeWorld; // Documentation : https://nomis80.org/code/doc/classOctree.html
		int m_SizeWorld;
		Selector* m_selector;
		interaction::CubeTextureList m_TextureList;


	public:
		CubeSelector() = delete;
		CubeSelector(renderer::CubeRenderer& renderer, const int& capacity = 2024);
		~CubeSelector();

		form::Cube* currentCube();
		form::Cube* currentSelected();
		void MoveSelector(const glm::vec3& deplacement);

		void Create(const glm::vec3& position, const Texture* texture, const int& scale);
		void Delete(form::Cube* cube);

		void MoveIn();
		void MoveOut();
		void AddToSelector();
		void DeleteToSelector();

		void Extrude();
		void Dig();

		void Show(glm::mat4 view, glm::mat4 projection);


	};

}

