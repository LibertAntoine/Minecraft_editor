#pragma once

/**
 * \file Interface.h
 * \brief Manage the ImGui interface and its interactions.
 * \author Antoine Libert & Nicolas Lienart
 */

#include <iostream>
#include <filesystem>

#include "ImGUI/imgui.h"
#include "SDL.h"

#include "GraphicEngine/App.h"
#include "GraphicEngine/Camera.h"
#include "GraphicEngine/Texture.h"

#include "MinecraftEditor/Interaction/CubeSelector.h"

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

		std::vector<std::string> m_filePaths;
		int m_selectedFile;
		std::string m_newFile = "untitled";

		float m_actionMenuWitdh;
		bool m_open;

	public:
		Interface(std::shared_ptr<renderer::CubeRenderer> renderer, std::shared_ptr<interaction::CubeSelector> selector, std::shared_ptr<TextureArray> textureArray, 
			std::shared_ptr<camera::FreeflyCamera> camera, std::shared_ptr<interaction::LightManager> light, std::shared_ptr<glm::vec3> backgroundColor);
		~Interface();

		/* MENU */
		/**
		* \brief Active the menu which the different controller panel.
		*/
		void MainActionMenu();

		/**
		* \brief Active the bar menu.
		*/
		void MenuBarInterface();

		/**
		* \brief Active the navigation menu with infos relative to the selector and current cube selected.
		*/
		void MenuInfosInterface();
		

		/* CONTROLLER */

		/**
		* \brief Active grid panel controller.
		*/
		void GridController();
		/**
		* \brief Active world panel controller (color of the world).
		*/
		void WorldController();
		/**
		* \brief Active save/load panel controller.
		*/
		void SaveController();
		/**
		* \brief Active the cube panel controller (add/delete/extrude...).
		*/
		void CubeController();
		/**
		* \brief Active the light panel controller.
		*/
		void LightController();
		/**
		* \brief Active the camera panel controller.
		*/
		void CameraController();
		/**
		* \brief Active the RBF panel controller.
		*/
		void RBFController();


		/* INFOS - SELECTOR CONTROLLER */
		/**
		* \brief Active the infos panel/controller relative to the cube selected.
		*/
		void InfosCurrentCubeInterface();
		/**
		* \brief Active the infos panel/controller relative to the selector.
		*/
		void InfosSelectorInterface();

	private:
		/* ImGUI WIDGET */

        void RBFFile(interaction::CubeSelector& cubeSelector, const char* label);
				void SceneFiles(const char* label);
		/**
		* \brief Create a combo button to select one texture.
		* \param Texture that modified the combo.
		* \param Label of the combo button.
		*/
		void ComboTexture(std::vector<unsigned int>& textures, const char* label);
		/**
		* \brief Create a suite of six combo buttons to select six textures (for each face of a cube).
		* \param Texture array of the six textures that the combos modified.
		* \param Label of the combo buttons.
		*/
		void ComboMultiTexture(std::vector<unsigned int>& textures, const char* label);

		void findFiles();
	};

}
