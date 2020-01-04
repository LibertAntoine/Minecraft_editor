#pragma once

/**
 * \file Mode.h
 * \brief Abstract Class Which Manage the Mode system
 * \author Antoine Libert & Nicolas Lienart
 * The child classes allow to the program to have different under-application
 * associate to a ImguiMenu to navigate between its.
 * ModeMenu is a speacial mode which give access to the différent under-application
 */

#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <SDL.h>

namespace Modes {
	
	/**
	* \brief A child of this abstract class is an under-application of the program.
	*/
	class Mode
	{
	public:
		Mode() {}
		virtual ~Mode() {}

		// Action of the mode each frame //
		virtual void OnUpdate(float ) {}

		// Reaction relative to the event each frame //
		virtual void OnEvent(const SDL_Event& ) {}

		// Graphic render of the mode each frame //
		virtual void OnRender() {}

		// Render specific of ImGui for this mode each frame //
		virtual void OnImGuiRender() {}
	};

	class ModeMenu : public Mode
	{
	public:
		ModeMenu(Mode*& currentModePointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterMode(const std::string& name)
		{
			std::cout << "Registering mode " << name << std::endl;
			m_Modes.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Mode*& m_CurrentMode;
		std::vector < std::pair<std::string, std::function<Mode*()>>> m_Modes;
	};
}
