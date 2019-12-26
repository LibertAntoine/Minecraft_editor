#pragma once

#include "Mode.h"

namespace modes {
	class ModeClearColor : public Mode
	{
	public:
		ModeClearColor();
		~ModeClearColor();
		void OnUpdate(float deltaTime) override;
		void OnEvent(const SDL_Event& e) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};


}