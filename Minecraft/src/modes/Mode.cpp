#include "Mode.h"
#include "ImGUI/imgui.h"

namespace mode {

	ModeMenu::ModeMenu(Mode*& currentTestPointer)
		: m_CurrentMode(currentTestPointer)
	{

	}

	void ModeMenu::OnImGuiRender()
	{
		for (auto& mode : m_Modes)
		{
			if (ImGui::Button(mode.first.c_str()))
				m_CurrentMode = mode.second();
				
		}
	}

}