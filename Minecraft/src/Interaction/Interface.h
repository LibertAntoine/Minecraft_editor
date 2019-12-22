#pragma once
#include "ImGUI/imgui.h"
#include "SDL.h"
#include "Interaction/CubeSelector.h"
#include "Camera.h"
#include <iostream>
#include "App.h"
#include "Texture.h"


namespace interaction {

	class Interface
	{
	private:
		float m_actionMenuWitdh;
		bool m_open;

	public:
		Interface();
		~Interface();
		void MainActionMenu(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		void CameraInterface(camera::FreeflyCamera& Camera);
		void MenuBarInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		void MenuInfosInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		void InfosCurrentCubeInterface(interaction::CubeSelector& cubeSelector);
		void InfosSelectorInterface(interaction::CubeSelector& cubeSelector);
		void ComboTexture(interaction::CubeSelector& cubeSelector, Texture** texture, const char* label);
	};

}
