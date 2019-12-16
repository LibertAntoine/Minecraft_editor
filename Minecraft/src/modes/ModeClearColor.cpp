#include "ModeClearColor.h"
#include "Renderer.h"
#include "ImGUI/imgui.h"

namespace mode {

	ModeClearColor::ModeClearColor()
		: m_ClearColor { 0.2f, 0.3f, 0.8, 1.0f }
	{

	}

	ModeClearColor::~ModeClearColor()
	{

	}

	void ModeClearColor::OnUpdate(float deltaTime)
	{

	}

	void ModeClearColor::OnEvent(SDL_Event& e)
	{

	}

	void ModeClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}


	void ModeClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}