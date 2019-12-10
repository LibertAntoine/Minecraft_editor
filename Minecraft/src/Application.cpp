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
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("An SDL2 window",
		SDL_WINDOWPOS_CENTERED,           // initial x position
		SDL_WINDOWPOS_CENTERED,           // initial y position
		1080,                               // width, in pixels
		720,                               // height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL                  // flags - see below
	);

	if (window == NULL) {
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);


	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context)
	{
		std::cerr << "Unable to create GL context:" << SDL_GetError() << std::endl;
		return 1;
	}

	const auto result = glewInit();
	if (result != GLEW_OK)
	{
		const auto* error = glewGetErrorString(result);
		std::cout << "Error glew init: " << error << std::endl;
	}
	 
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	Renderer renderer;
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
	testMenu->RegisterTest<test::ModePlanette>("Mode Planette");

	/* Boucle principale */
	int loop = 1;
	while (loop)
	{

		/* Placer ici le code de dessin */
		glClear(GL_COLOR_BUFFER_BIT);


		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			/* L'utilisateur ferme la fenetre : */
			if (e.type == SDL_QUIT)
			{
				loop = 0;
				break;
			}
		}

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
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



		/* Echange du front et du back buffer : mise a jour de la fenetre */
		SDL_GL_SwapWindow(window);

	}

	delete currentTest;
	if (currentTest != testMenu) {
		delete testMenu;
	}



		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		// Close and destroy the window
		SDL_DestroyWindow(window);

		// Clean up
		SDL_Quit();

		return 0;
}