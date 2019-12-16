#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <iostream>
#include <SDL.h>

namespace mode {

	class Mode
	{
	public:
		Mode() {}
		virtual ~Mode() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent(SDL_Event &e) {}
		virtual void OnRender() {}
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
