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

	typedef enum SelectorState {
		NEUTRAL = 0,
		SELECTED = 1,
		COPY = 2
	} SelectorState;

	typedef struct Selector {
		form::Cube selectorCube;
		form::Cube* currentCube;
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
		bool m_activeGrid[3];

	public:
		CubeSelector() = delete;
		CubeSelector(renderer::CubeRenderer& renderer, const int& capacity = 2024);
		~CubeSelector();

		inline Selector* selector() { return m_selector; };
		inline form::Cube* currentCube() { return m_selector->currentCube; };
		inline form::Cube& selectorCube() { return m_selector->selectorCube; };
		inline interaction::CubeTextureList* textureList() { return &m_TextureList; };
		inline const int sizeWorld() const { return m_SizeWorld; };
		inline const bool* activeGrid() const { return m_activeGrid; };
		inline bool* activeGrid() { return m_activeGrid; };


		void refresh();
		form::Cube* currentSelected();
		void MoveSelector(const glm::ivec3& deplacement);
		void SetSelector(const glm::ivec3& NewPosition);
		void Move(form::Cube* cube, const glm::vec3& newPosition);
		void Create(const form::Cube& cube);
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

