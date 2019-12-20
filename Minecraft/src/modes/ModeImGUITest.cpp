
#include "ModeImGUITest.h"
#include "ImGUI/imgui.h"


namespace mode {

	ModeImGUITest::ModeImGUITest()

	{
		
	}

	ModeImGUITest::~ModeImGUITest()
	{

	}

	void ModeImGUITest::OnEvent(const SDL_Event& e)
	{

	}

	void ModeImGUITest::OnUpdate(float deltaTime)
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