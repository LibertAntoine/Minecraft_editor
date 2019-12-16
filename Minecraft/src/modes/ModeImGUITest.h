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
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
