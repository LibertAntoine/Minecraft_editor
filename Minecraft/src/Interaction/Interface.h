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
		void MainActionMenu(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector, interaction::LightManager& lightManager);
		void CameraInterface(interaction::CubeSelector& cubeSelector, camera::FreeflyCamera& Camera);
		void MenuBarInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		void MenuInfosInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		void InfosCurrentCubeInterface(interaction::CubeSelector& cubeSelector);
		void InfosSelectorInterface(interaction::CubeSelector& cubeSelector);
		void GridController(interaction::CubeSelector& cubeSelector);
		void LightController(interaction::CubeSelector& cubeSelector, interaction::LightManager& lightManager);
		void ComboTexture(interaction::CubeSelector& cubeSelector, std::vector<Texture*>& textures, const char* label);
		void ComboMultiTexture(interaction::CubeSelector& cubeSelector, std::vector<Texture*>& textures, const char* label);
		bool DragIntSameLine(const char* label, const int& nb, int* value, const int& step = 1, const int& min = 0, const int& max = 100, const char* symbol = "");
	};

}
