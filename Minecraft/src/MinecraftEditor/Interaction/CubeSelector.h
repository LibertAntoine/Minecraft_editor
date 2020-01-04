#pragma once

/**
 * \file CubeSelector.h
 * \brief Manage all the interaction relative to the cube selection
 * \author Antoine Libert & Nicolas Lienart
 * Contains the add/delete/extrude/dig/move logic of the cubes.
 */

#include <iostream>
#include "GraphicEngine/VertexBuffer.h"
#include "GraphicEngine/FrameBuffer.h"
#include "GraphicEngine/VertexBufferLayout.h"
#include <vector>
#include <memory> // For std::make_unique
#include <algorithm>
#include "MinecraftEditor/Graphic/Forms/Cube.h"
#include <octree/octree.h>
#include "MinecraftEditor/Graphic/Renderers/CubeRenderer.h"
#include "RBF.h"


namespace interaction {


	/**
	* \brief State of the selector, indicate if the selector is currently in a cut or copy action.
	*/
	typedef enum SelectorState {
		NEUTRAL = 0,
		CUT = 1,
		COPY = 2
	} SelectorState;

	/**
	* \brief Contains data relative to the selector.
	*/
	typedef struct Selector {
		Forms::Cube selectorCube;
		Forms::Cube* currentCube;
		SelectorState selectorState;
		glm::vec3 selectedPosition;
	} Selector;

	class CubeSelector
	{
	private:
		std::shared_ptr<renderer::CubeRenderer> m_Cuberenderer;
		int m_SizeWorld;
		Octree<Forms::Cube*> m_CubeWorld; 
		Selector* m_selector;
		bool m_activeGrid[3];

		std::shared_ptr<Texture> m_textSelector;
		std::shared_ptr<Texture> m_textCut;
		std::shared_ptr<Texture> m_textCopy;


	public:
        RBF m_rbf; //TODO: go to private w/ getter

		CubeSelector() = delete;

		/**
		* \brief Create a selector
		* \param Renderer used for the selector render.
		*/
		CubeSelector(std::shared_ptr<renderer::CubeRenderer> renderer, const int& capacity = 2024);
		~CubeSelector();


		// GETTERS - SETTERS //
		inline Selector* selector() { return m_selector; };
		inline Forms::Cube* currentCube() { return m_selector->currentCube; };
		inline Forms::Cube& selectorCube() { return m_selector->selectorCube; };
		inline int sizeWorld() const { return m_SizeWorld; };
		inline const bool* activeGrid() const { return m_activeGrid; };
		inline bool* activeGrid() { return m_activeGrid; };
		std::shared_ptr<Texture> textSelected() { return m_textCut; };
		std::shared_ptr<Texture> textSelector() { return m_textSelector; };
		Forms::Cube* currentSelected();

		/**
		* \brief Check which cube is currently selected.
		*/
		void refresh();

		/**
		* \brief Move the selector in function of relative deplacement.
		* \param deplacement x,y,z which correspond to the selector deplacement.
		*/
		void MoveSelector(const glm::ivec3& deplacement);

		/**
		* \brief Move the selector in function of an absolute position.
		* \param NewPosition of the selector.
		*/
		void SetSelector(const glm::ivec3& NewPosition);

		/**
		* \brief Move a cube in the scene.
		* \param cube to move
		* \param NewPosition of the cube.
		*/
		void Move(Forms::Cube* cube, const glm::vec3& newPosition);

		/**
		* \brief Create a new cube in the scene.
		* \param cube to add in the scene.
		*/
		void Create(const Forms::Cube& cube);

		/**
		* \brief Delete a cube on the scene.
		* \param *cube to delete in the scene.
		*/
		void Delete(Forms::Cube* cube);


		/**
		* \brief Add a new cube in the scene at the current selector position, with the selector presets.
		*/
		void AddToSelector();

		/**
		* \brief Delete the cube (if existing) at the current selector position.
		*/
		void DeleteToSelector();

		/**
		* \brief Extrude in the current column of the selector.
		* The new cube take the preset of the cube below, or selector preset if no cube in the column.
		* Move the selector on this cube.
		*/
		void Extrude();

		/**
		* \brief Dig in the current column of the selector, if there is a cube.
		* Move the selector at the position below the cube delete.
		*/
		void Dig();

		/**
		* \brief Cut the cube currently selected in the scene, it will be moved when Paste() called.
		* \param *cube to delete in the scene.
		*/
		void CutToSelector();

		/**
		* \brief If a cube has been cut, it is moved at the current selector position.
		*/
		void PasteToSelector();

		void ApplyRBF();
		void MoveSelectorToClick(int x, int y, const FrameBuffer& framebufferSelection);
		void MoveSelectorToClickFace(int x, int y, const FrameBuffer& framebufferSelection);

	private:
		Forms::Cube* giveHighestCube();

	};

}

