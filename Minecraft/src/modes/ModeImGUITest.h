#pragma once

#include "Mode.h"

#include <memory>

namespace Modes {
	class ModeImGUITest : public Mode
	{
	public:
		ModeImGUITest();
		~ModeImGUITest();
		void OnUpdate(float ) override;
		void OnEvent(const SDL_Event& ) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
