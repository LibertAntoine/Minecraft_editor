#pragma once

/**
 * \file KeyBoard.h
 * \brief Manage the keyboard and mouse shorcut.
 * \author Antoine Libert & Nicolas Lienart
 */

#include <iostream>

#include "ImGUI/imgui.h"
#include "SDL.h"

#include "GraphicEngine/App.h"
#include "GraphicEngine/Camera.h"

#include "MinecraftEditor/Interaction/CubeSelector.h"

namespace interaction {

	class KeyBoard
	{
	private:
		std::shared_ptr<renderer::CubeRenderer> m_cubeRenderer;
		std::shared_ptr<interaction::CubeSelector> m_cubeSelector;
		std::shared_ptr<camera::FreeflyCamera> m_camera;
		FrameBuffer* m_frameBufferSelection;

		bool m_LayerDraw = false; /// \var enabled when drawing or erasing a layer
		int m_yLayer; /// \var enabled when drawing or erasing a layer

	public:
		/**
		* \brief Init Keyboard
		* \param cubeRenderer of the application
		* \param selector of the application
		* \param camera of the application
		* \param frameBufferSelection of the application
		*/
		KeyBoard(std::shared_ptr<renderer::CubeRenderer> cubeRenderer, std::shared_ptr<interaction::CubeSelector> selector, std::shared_ptr<camera::FreeflyCamera> camera, FrameBuffer* frameBufferSelection);
		~KeyBoard();

		/**
		* \brief Active Shorcuts relative to the Camera.
		*/
		void CameraShortCut();
		/**
		* \brief Active Shorcuts relative to the cubes.
		*/
		void CubeShortCut();
		/**
		* \brief Active Shorcuts relative to the selector.
		*/
		void SelectorShortCut();
		/**
		* \brief Active Mouse Shorcuts
		*/
		void MouseShortCut();
	};

}
