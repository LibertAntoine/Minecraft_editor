#pragma once

#include <iostream>
#include "VertexBuffer.h"
#include "FrameBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include "forms/Cube.h"
#include <octree/octree.h>
#include <Renderer/CubeRenderer.h>
#include "RBF.h"

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
		std::shared_ptr<renderer::CubeRenderer> m_Cuberenderer;
		std::shared_ptr<TextureArray> m_TextureArray;
		int m_SizeWorld;
		Octree<form::Cube*> m_CubeWorld; // Documentation : https://nomis80.org/code/doc/classOctree.html
		Selector* m_selector;
		bool m_activeGrid[3];

		std::shared_ptr<Texture> m_textSelector;
		std::shared_ptr<Texture> m_textSelected;
		std::shared_ptr<Texture> m_textCopy;


	public:
                RBF m_rbf; //TODO: go to private w/ getter

		CubeSelector() = delete;
		CubeSelector(std::shared_ptr<renderer::CubeRenderer> renderer, std::shared_ptr<TextureArray> textureArray, const int& capacity = 2024);
		~CubeSelector();

		inline Selector* selector() { return m_selector; };
		inline form::Cube* currentCube() { return m_selector->currentCube; };
		inline form::Cube& selectorCube() { return m_selector->selectorCube; };
		inline int sizeWorld() const { return m_SizeWorld; };
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

		void ApplyRBF();

		void Extrude();
		void Dig();

		void Show(glm::mat4 view, glm::mat4 projection);

		void MoveSelectorToClick(int x, int y, const FrameBuffer& framebufferSelection);
		void MoveSelectorToClickFace(int x, int y, const FrameBuffer& framebufferSelection);
	};

}

