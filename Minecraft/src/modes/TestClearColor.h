#pragma once

#include "Mode.h"

namespace mode {
	class ModeClearColor : public Test
	{
	public:
		ModeClearColor();
		~ModeClearColor();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};


}