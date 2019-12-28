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

		/* MENU */
		void MainActionMenu(interaction::CubeSelector& cubeSelector, camera::FreeflyCamera& Camera, interaction::LightManager& lightManager, glm::vec3& backgroundColor);
		void MenuBarInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		void MenuInfosInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector);
		

		/* CONTROLLER */
		void GridController(interaction::CubeSelector& cubeSelector);
		void WorldController(glm::vec3& backgroundColor);
		void RBFController(interaction::CubeSelector& cubeSelector);
		void CubeController(interaction::CubeSelector& cubeSelector);
		void LightController(interaction::CubeSelector& cubeSelector, interaction::LightManager& lightManager);
		void CameraController(interaction::CubeSelector& cubeSelector, camera::FreeflyCamera& Camera);


		/* INFOS - SELECTOR CONTROLLER */
		void InfosCurrentCubeInterface(interaction::CubeSelector& cubeSelector);
		void InfosSelectorInterface(interaction::CubeSelector& cubeSelector);

		void CameraKeyBoard(camera::FreeflyCamera& camera);
		void CubeKeyBoard(interaction::CubeSelector& cubeSelector);
		void SelectorKeyBoard(interaction::CubeSelector& cubeSelector);

		/* ImGUI WIDGET */
		void ComboTexture(interaction::CubeSelector& cubeSelector, std::vector<Texture*>& textures, const char* label);
                void RBFFile(interaction::CubeSelector& cubeSelector, const char* label);
		void ComboMultiTexture(interaction::CubeSelector& cubeSelector, std::vector<Texture*>& textures, const char* label);
		bool DragIntSameLine(const char* label, const int& nb, int* value, const int& step = 1, const int& min = 0, const int& max = 100, const char* symbol = "");
	};

}
