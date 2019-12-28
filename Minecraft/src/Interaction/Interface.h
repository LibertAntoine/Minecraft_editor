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
		std::shared_ptr<renderer::CubeRenderer> m_cubeRenderer;
		std::shared_ptr<interaction::CubeSelector> m_cubeSelector;
		std::shared_ptr<TextureArray> m_textureArray;
		std::shared_ptr<camera::FreeflyCamera> m_camera;
		std::shared_ptr<interaction::LightManager> m_light;
		std::shared_ptr<glm::vec3> m_backgroundColor;
		float m_actionMenuWitdh;
		bool m_open;

	public:
		Interface(renderer::CubeRenderer& renderer, interaction::CubeSelector& selector, TextureArray& textureArray, 
			camera::FreeflyCamera& camera, interaction::LightManager& light, glm::vec3& backgroundColor);
		~Interface();

		/* MENU */
		void MainActionMenu();
		void MenuBarInterface();
		void MenuInfosInterface();
		

		/* CONTROLLER */
		void RBFController(interaction::CubeSelector& cubeSelector);
		void GridController();
		void WorldController();
		void CubeController();
		void LightController();
		void CameraController();


		/* INFOS - SELECTOR CONTROLLER */
		void InfosCurrentCubeInterface();
		void InfosSelectorInterface();

		void CameraKeyBoard();
		void CubeKeyBoard();
		void SelectorKeyBoard();

	private:
		/* ImGUI WIDGET */
                void RBFFile(interaction::CubeSelector& cubeSelector, const char* label);
		void ComboTexture(std::vector<unsigned int>& textures, const char* label);
		void ComboMultiTexture(std::vector<unsigned int>& textures, const char* label);
		bool DragIntSameLine(const char* label, const int& nb, int* value, const int& step = 1, const int& min = 0, const int& max = 100, const char* symbol = "");
	};

}
