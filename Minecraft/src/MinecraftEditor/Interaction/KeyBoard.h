#pragma once

/**
 * \file Interface.h
 * \brief Manage the ImGui interface and its interactions.
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

	public:
		KeyBoard(std::shared_ptr<renderer::CubeRenderer> cubeRenderer, std::shared_ptr<interaction::CubeSelector> selector, std::shared_ptr<camera::FreeflyCamera> camera, FrameBuffer* frameBufferSelection);
		~KeyBoard();


		void CameraShortCut();
		void CubeShortCut();
		void SelectorShortCut();
		void MouseShortCut();
	};

}