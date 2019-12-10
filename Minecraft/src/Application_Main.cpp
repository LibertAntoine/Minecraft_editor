#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include <stdio.h>

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "App.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/ModePlanette.h"

int main(int argc, char* argv[])
{
	App app;
	Renderer renderer;

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
	testMenu->RegisterTest<test::ModePlanette>("Mode Planette");

	/* Boucle principale */
	while (app.isRunning()) {
		{
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				/* L'utilisateur ferme la fenetre : */
				if (e.type == SDL_QUIT)
				{
					app.exit();
					break;
				}
			}

			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();
			app.beginFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			app.endFrame();

		}

	}

	delete currentTest;
	if (currentTest != testMenu) {
		delete testMenu;
	}



		return 0;
}