#pragma once

#include "Mode.h"

#include <memory>

namespace mode {
	class ModeImGUITest : public Mode
	{
	public:
		ModeImGUITest();
		~ModeImGUITest();
		void OnUpdate(float deltaTime) override;
		void OnEvent(SDL_Event& e) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
