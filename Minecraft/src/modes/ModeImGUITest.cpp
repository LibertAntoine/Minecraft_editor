
#include "ModeImGUITest.h"
#include "ImGUI/imgui.h"


namespace modes {

	ModeImGUITest::ModeImGUITest()

	{
		
	}

	ModeImGUITest::~ModeImGUITest()
	{

	}

	void ModeImGUITest::OnEvent(const SDL_Event& )
	{

	}

	void ModeImGUITest::OnUpdate(float )
	{

	}

	void ModeImGUITest::OnRender()
	{

	}


	void ModeImGUITest::OnImGuiRender()
	{
		ImGui::ShowDemoWindow();
	}
}
